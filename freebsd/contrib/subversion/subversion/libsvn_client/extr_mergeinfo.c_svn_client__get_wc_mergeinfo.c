#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ svn_revnum_t ;
typedef  int /*<<< orphan*/ * svn_mergeinfo_t ;
typedef  scalar_t__ svn_mergeinfo_inheritance_t ;
struct TYPE_14__ {scalar_t__ apr_err; } ;
typedef  TYPE_1__ svn_error_t ;
struct TYPE_15__ {int /*<<< orphan*/  wc_ctx; } ;
typedef  TYPE_2__ svn_client_ctx_t ;
typedef  scalar_t__ svn_boolean_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 scalar_t__ FALSE ; 
 int /*<<< orphan*/  SVN_ERR (TYPE_1__*) ; 
 int /*<<< orphan*/  SVN_ERR_ASSERT (int /*<<< orphan*/ ) ; 
 scalar_t__ SVN_ERR_MERGEINFO_PARSE_ERROR ; 
 int /*<<< orphan*/  SVN_INVALID_REVNUM ; 
 scalar_t__ SVN_IS_VALID_REVNUM (scalar_t__) ; 
 TYPE_1__* SVN_NO_ERROR ; 
 scalar_t__ TRUE ; 
 scalar_t__ apr_hash_count (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * apr_hash_make (int /*<<< orphan*/ *) ; 
 scalar_t__ strcmp (char const*,char const*) ; 
 int /*<<< orphan*/  strlen (char const*) ; 
 TYPE_1__* svn_client__parse_mergeinfo (int /*<<< orphan*/ **,int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_dirent_basename (char const*,int /*<<< orphan*/ *) ; 
 char* svn_dirent_dirname (char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_dirent_is_absolute (char const*) ; 
 int /*<<< orphan*/  svn_dirent_is_root (char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_error_clear (TYPE_1__*) ; 
 TYPE_1__* svn_mergeinfo__add_suffix_to_mergeinfo (int /*<<< orphan*/ **,int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_mergeinfo__remove_empty_rangelists (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ svn_mergeinfo_explicit ; 
 TYPE_1__* svn_mergeinfo_inheritable2 (int /*<<< orphan*/ **,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ svn_mergeinfo_inherited ; 
 scalar_t__ svn_mergeinfo_nearest_ancestor ; 
 scalar_t__ svn_path_is_empty (char const*) ; 
 int /*<<< orphan*/  svn_pool_clear (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_pool_create (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_pool_destroy (int /*<<< orphan*/ *) ; 
 char* svn_relpath_join (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ *) ; 
 TYPE_1__* svn_wc__node_get_base (int /*<<< orphan*/ *,scalar_t__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char const*,scalar_t__,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 TYPE_1__* svn_wc__node_get_changed_info (scalar_t__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 TYPE_1__* svn_wc_check_root (scalar_t__*,scalar_t__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ *) ; 

svn_error_t *
svn_client__get_wc_mergeinfo(svn_mergeinfo_t *mergeinfo,
                             svn_boolean_t *inherited_p,
                             svn_mergeinfo_inheritance_t inherit,
                             const char *local_abspath,
                             const char *limit_abspath,
                             const char **walked_path,
                             svn_boolean_t ignore_invalid_mergeinfo,
                             svn_client_ctx_t *ctx,
                             apr_pool_t *result_pool,
                             apr_pool_t *scratch_pool)
{
  const char *walk_relpath = "";
  svn_mergeinfo_t wc_mergeinfo;
  svn_revnum_t base_revision;
  apr_pool_t *iterpool;
  svn_boolean_t inherited;

  SVN_ERR_ASSERT(svn_dirent_is_absolute(local_abspath));
  if (limit_abspath)
    SVN_ERR_ASSERT(svn_dirent_is_absolute(limit_abspath));

  SVN_ERR(svn_wc__node_get_base(NULL, &base_revision, NULL, NULL, NULL, NULL,
                                ctx->wc_ctx, local_abspath,
                                TRUE /* ignore_enoent */,
                                scratch_pool, scratch_pool));

  iterpool = svn_pool_create(scratch_pool);
  while (TRUE)
    {
      svn_pool_clear(iterpool);

      /* Don't look for explicit mergeinfo on LOCAL_ABSPATH if we are only
         interested in inherited mergeinfo. */
      if (inherit == svn_mergeinfo_nearest_ancestor)
        {
          wc_mergeinfo = NULL;
          inherit = svn_mergeinfo_inherited;
        }
      else
        {
          /* Look for mergeinfo on LOCAL_ABSPATH.  If there isn't any and we
             want inherited mergeinfo, walk towards the root of the WC until
             we encounter either (a) an unversioned directory, or
             (b) mergeinfo.  If we encounter (b), use that inherited
             mergeinfo as our baseline. */
          svn_error_t *err = svn_client__parse_mergeinfo(&wc_mergeinfo,
                                                         ctx->wc_ctx,
                                                         local_abspath,
                                                         result_pool,
                                                         iterpool);
          if ((ignore_invalid_mergeinfo || walk_relpath [0] != '\0')
              && err
              && err->apr_err == SVN_ERR_MERGEINFO_PARSE_ERROR)
            {
              svn_error_clear(err);
              wc_mergeinfo = apr_hash_make(result_pool);
              break;
            }
          else
            {
              SVN_ERR(err);
            }
        }

      if (wc_mergeinfo == NULL &&
          inherit != svn_mergeinfo_explicit &&
          !svn_dirent_is_root(local_abspath, strlen(local_abspath)))
        {
          svn_boolean_t is_wc_root;
          svn_boolean_t is_switched;
          svn_revnum_t parent_base_rev;
          svn_revnum_t parent_changed_rev;

          /* Don't look any higher than the limit path. */
          if (limit_abspath && strcmp(limit_abspath, local_abspath) == 0)
            break;

          /* If we've reached the root of the working copy don't look any
             higher. */
          SVN_ERR(svn_wc_check_root(&is_wc_root, &is_switched, NULL,
                                    ctx->wc_ctx, local_abspath, iterpool));
          if (is_wc_root || is_switched)
            break;

          /* No explicit mergeinfo on this path.  Look higher up the
             directory tree while keeping track of what we've walked. */
          walk_relpath = svn_relpath_join(svn_dirent_basename(local_abspath,
                                                              iterpool),
                                          walk_relpath, result_pool);
          local_abspath = svn_dirent_dirname(local_abspath, scratch_pool);

          SVN_ERR(svn_wc__node_get_base(NULL, &parent_base_rev, NULL, NULL,
                                        NULL, NULL,
                                        ctx->wc_ctx, local_abspath,
                                        TRUE /* ignore_enoent */,
                                        scratch_pool, scratch_pool));

          /* ### This checks the WORKING changed_rev, so invalid on replacement
             ### not even reliable in case an ancestor was copied from a
             ### different location */
          SVN_ERR(svn_wc__node_get_changed_info(&parent_changed_rev,
                                                NULL, NULL,
                                                ctx->wc_ctx, local_abspath,
                                                scratch_pool,
                                                scratch_pool));

          /* Look in LOCAL_ABSPATH's parent for inherited mergeinfo if
             LOCAL_ABSPATH has no base revision because it is an uncommitted
             addition, or if its base revision falls within the inclusive
             range of its parent's last changed revision to the parent's base
             revision; otherwise stop looking for inherited mergeinfo. */
          if (SVN_IS_VALID_REVNUM(base_revision)
              && (base_revision < parent_changed_rev
                  || parent_base_rev < base_revision))
            break;

          /* We haven't yet risen above the root of the WC. */
          continue;
        }
      break;
    }

  svn_pool_destroy(iterpool);

  if (svn_path_is_empty(walk_relpath))
    {
      /* Mergeinfo is explicit. */
      inherited = FALSE;
      *mergeinfo = wc_mergeinfo;
    }
  else
    {
      /* Mergeinfo may be inherited. */
      if (wc_mergeinfo)
        {
          inherited = TRUE;
          SVN_ERR(svn_mergeinfo__add_suffix_to_mergeinfo(mergeinfo,
                                                         wc_mergeinfo,
                                                         walk_relpath,
                                                         result_pool,
                                                         scratch_pool));
        }
      else
        {
          inherited = FALSE;
          *mergeinfo = NULL;
        }
    }

  if (walked_path)
    *walked_path = walk_relpath;

  /* Remove non-inheritable mergeinfo and paths mapped to empty ranges
     which may occur if WCPATH's mergeinfo is not explicit. */
  if (inherited
      && apr_hash_count(*mergeinfo)) /* Nothing to do for empty mergeinfo. */
    {
      SVN_ERR(svn_mergeinfo_inheritable2(mergeinfo, *mergeinfo, NULL,
                                         SVN_INVALID_REVNUM, SVN_INVALID_REVNUM,
                                         TRUE, result_pool, scratch_pool));
      svn_mergeinfo__remove_empty_rangelists(*mergeinfo, scratch_pool);
    }

  if (inherited_p)
    *inherited_p = inherited;

  return SVN_NO_ERROR;
}