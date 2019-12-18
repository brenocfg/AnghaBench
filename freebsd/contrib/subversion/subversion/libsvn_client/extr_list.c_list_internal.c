#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_25__   TYPE_5__ ;
typedef  struct TYPE_24__   TYPE_4__ ;
typedef  struct TYPE_23__   TYPE_2__ ;
typedef  struct TYPE_22__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  svn_ra_session_t ;
typedef  int /*<<< orphan*/  svn_opt_revision_t ;
typedef  int /*<<< orphan*/  svn_membuf_t ;
struct TYPE_22__ {scalar_t__ apr_err; } ;
typedef  TYPE_1__ svn_error_t ;
struct TYPE_23__ {scalar_t__ kind; } ;
typedef  TYPE_2__ svn_dirent_t ;
typedef  int /*<<< orphan*/  svn_depth_t ;
typedef  int /*<<< orphan*/  (* svn_client_list_func2_t ) (void*,char*,TYPE_2__*,int /*<<< orphan*/ *,char const*,char const*,char const*,int /*<<< orphan*/ *) ;
typedef  int /*<<< orphan*/  svn_client_ctx_t ;
struct TYPE_24__ {int /*<<< orphan*/  rev; int /*<<< orphan*/  url; } ;
typedef  TYPE_4__ svn_client__pathrev_t ;
typedef  scalar_t__ svn_boolean_t ;
struct TYPE_25__ {char const* fs_base_path; int /*<<< orphan*/ * locks; int /*<<< orphan*/  (* list_func ) (void*,char*,TYPE_2__*,int /*<<< orphan*/ *,char const*,char const*,char const*,int /*<<< orphan*/ *) ;int /*<<< orphan*/ * ctx; void* list_baton; } ;
typedef  TYPE_5__ receiver_baton_t ;
typedef  int /*<<< orphan*/  apr_uint32_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;
typedef  int /*<<< orphan*/  apr_hash_t ;
typedef  int /*<<< orphan*/  apr_array_header_t ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_DIRENT_KIND ; 
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SVN_ERR_FS_NOT_FOUND ; 
 scalar_t__ SVN_ERR_RA_NOT_IMPLEMENTED ; 
 int /*<<< orphan*/  SVN_ERR_UNSUPPORTED_FEATURE ; 
 TYPE_1__* SVN_NO_ERROR ; 
 int /*<<< orphan*/  _ (char*) ; 
 scalar_t__ apr_hash_count (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * apr_hash_make (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  get_dir_contents (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,char const*,int /*<<< orphan*/  const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,char const*,char const*,int /*<<< orphan*/  (*) (void*,char*,TYPE_2__*,int /*<<< orphan*/ *,char const*,char const*,char const*,int /*<<< orphan*/ *),void*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_externals (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/  (*) (void*,char*,TYPE_2__*,int /*<<< orphan*/ *,char const*,char const*,char const*,int /*<<< orphan*/ *),void*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_receiver ; 
 scalar_t__ match_patterns (int /*<<< orphan*/ ,int /*<<< orphan*/  const*,int /*<<< orphan*/ *) ; 
 char* svn_client__pathrev_fspath (TYPE_4__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_client__ra_session_from_path2 (int /*<<< orphan*/ **,TYPE_4__**,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_depth_files ; 
 int /*<<< orphan*/  svn_depth_immediates ; 
 int /*<<< orphan*/  svn_depth_infinity ; 
 int /*<<< orphan*/  svn_dirent_dirname (char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_error_clear (TYPE_1__*) ; 
 TYPE_1__* svn_error_createf (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ svn_error_find_cause (TYPE_1__*,int /*<<< orphan*/ ) ; 
 TYPE_1__* svn_error_trace (TYPE_1__*) ; 
 int /*<<< orphan*/ * svn_hash_gets (int /*<<< orphan*/ *,char const*) ; 
 int /*<<< orphan*/  svn_membuf__create (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *) ; 
 scalar_t__ svn_node_dir ; 
 TYPE_1__* svn_ra_get_locks2 (int /*<<< orphan*/ *,int /*<<< orphan*/ **,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 TYPE_1__* svn_ra_list (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int /*<<< orphan*/  const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_5__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_ra_stat (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,TYPE_2__**,int /*<<< orphan*/ *) ; 

__attribute__((used)) static svn_error_t *
list_internal(const char *path_or_url,
              const svn_opt_revision_t *peg_revision,
              const svn_opt_revision_t *revision,
              const apr_array_header_t *patterns,
              svn_depth_t depth,
              apr_uint32_t dirent_fields,
              svn_boolean_t fetch_locks,
              svn_boolean_t include_externals,
              const char *external_parent_url,
              const char *external_target,
              svn_client_list_func2_t list_func,
              void *baton,
              svn_client_ctx_t *ctx,
              apr_pool_t *pool)
{
  svn_ra_session_t *ra_session;
  svn_client__pathrev_t *loc;
  svn_dirent_t *dirent;
  const char *fs_path;
  svn_error_t *err;
  apr_hash_t *locks;
  apr_hash_t *externals;
  svn_membuf_t scratch_buffer;

  if (include_externals)
    externals = apr_hash_make(pool);
  else
    externals = NULL;

  /* We use the kind field to determine if we should recurse, so we
     always need it. */
  dirent_fields |= SVN_DIRENT_KIND;

  /* Get an RA plugin for this filesystem object. */
  SVN_ERR(svn_client__ra_session_from_path2(&ra_session, &loc,
                                            path_or_url, NULL,
                                            peg_revision,
                                            revision, ctx, pool));

  fs_path = svn_client__pathrev_fspath(loc, pool);

  /* Maybe get all locks under url. */
  if (fetch_locks)
    {
      /* IMPORTANT: If locks are stored in a more temporary pool, we need
         to fix store_dirent below to duplicate the locks. */
      err = svn_ra_get_locks2(ra_session, &locks, "", depth, pool);

      if (err && err->apr_err == SVN_ERR_RA_NOT_IMPLEMENTED)
        {
          svn_error_clear(err);
          locks = NULL;
        }
      else if (err)
        return svn_error_trace(err);
    }
  else
    locks = NULL;

  /* Try to use the efficient and fully authz-filtered code path. */
  if (!include_externals)
    {
      receiver_baton_t receiver_baton;
      receiver_baton.list_baton = baton;
      receiver_baton.ctx = ctx;
      receiver_baton.list_func = list_func;
      receiver_baton.locks = locks;
      receiver_baton.fs_base_path = fs_path;

      err = svn_ra_list(ra_session, "", loc->rev, patterns, depth,
                        dirent_fields, list_receiver, &receiver_baton, pool);

      if (svn_error_find_cause(err, SVN_ERR_UNSUPPORTED_FEATURE))
        svn_error_clear(err);
      else
        return svn_error_trace(err);
    }

  /* Stat for the file / directory node itself. */
  SVN_ERR(svn_ra_stat(ra_session, "", loc->rev, &dirent, pool));
  if (! dirent)
    return svn_error_createf(SVN_ERR_FS_NOT_FOUND, NULL,
                             _("URL '%s' non-existent in revision %ld"),
                             loc->url, loc->rev);

  /* We need a scratch buffer for temporary string data.
   * Create one with a reasonable initial size. */
  svn_membuf__create(&scratch_buffer, 256, pool);

  /* Report the dirent for the target. */
  if (match_patterns(svn_dirent_dirname(fs_path, pool), patterns,
                     &scratch_buffer))
    SVN_ERR(list_func(baton, "", dirent, locks
                      ? (svn_hash_gets(locks, fs_path))
                      : NULL, fs_path, external_parent_url,
                      external_target, pool));

  if (dirent->kind == svn_node_dir
      && (depth == svn_depth_files
          || depth == svn_depth_immediates
          || depth == svn_depth_infinity))
    SVN_ERR(get_dir_contents(dirent_fields, "", loc->rev, ra_session, locks,
                             fs_path, patterns, depth, ctx, externals,
                             external_parent_url, external_target, list_func,
                             baton, &scratch_buffer, pool, pool));

  /* We handle externals after listing entries under path_or_url, so that
     handling external items (and any errors therefrom) doesn't delay
     the primary operation. */
  if (include_externals && apr_hash_count(externals))
    {
      /* The 'externals' hash populated by get_dir_contents() is processed
         here. */
      SVN_ERR(list_externals(externals, patterns, depth, dirent_fields,
                             fetch_locks, list_func, baton,
                             ctx, pool));
    }

  return SVN_NO_ERROR;
}