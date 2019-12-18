#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  svn_node_kind_t ;
struct TYPE_13__ {scalar_t__ apr_err; } ;
typedef  TYPE_1__ svn_error_t ;
typedef  int /*<<< orphan*/  svn_depth_t ;
struct TYPE_14__ {int /*<<< orphan*/  wc_ctx; } ;
typedef  TYPE_2__ svn_client_ctx_t ;
typedef  scalar_t__ svn_boolean_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 scalar_t__ FALSE ; 
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SVN_ERR_ENTRY_EXISTS ; 
 int /*<<< orphan*/  SVN_ERR_ILLEGAL_TARGET ; 
 scalar_t__ SVN_ERR_WC_NOT_WORKING_COPY ; 
 scalar_t__ SVN_ERR_WC_PATH_NOT_FOUND ; 
 TYPE_1__* SVN_NO_ERROR ; 
 int /*<<< orphan*/  SVN_WC__CALL_WITH_WRITE_LOCK (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char const*,scalar_t__,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  add (char const*,int /*<<< orphan*/ ,scalar_t__,scalar_t__,scalar_t__,char const*,TYPE_2__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  find_existing_parent (char const**,TYPE_2__*,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ strcmp (char const*,char const*) ; 
 char* svn_dirent_dirname (char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_dirent_get_absolute (char const**,char const*,int /*<<< orphan*/ *) ; 
 char const* svn_dirent_local_style (char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_error_clear (TYPE_1__*) ; 
 TYPE_1__* svn_error_createf (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char const*) ; 
 TYPE_1__* svn_error_trace (TYPE_1__*) ; 
 int /*<<< orphan*/  svn_io_check_special_path (char const*,int /*<<< orphan*/ *,scalar_t__*,int /*<<< orphan*/ *) ; 
 scalar_t__ svn_path_is_url (char const*) ; 
 int /*<<< orphan*/ * svn_pool_create (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_pool_destroy (int /*<<< orphan*/ *) ; 
 TYPE_1__* svn_wc__is_wcroot (scalar_t__*,int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ *) ; 

svn_error_t *
svn_client_add5(const char *path,
                svn_depth_t depth,
                svn_boolean_t force,
                svn_boolean_t no_ignore,
                svn_boolean_t no_autoprops,
                svn_boolean_t add_parents,
                svn_client_ctx_t *ctx,
                apr_pool_t *scratch_pool)
{
  const char *parent_abspath;
  const char *local_abspath;
  const char *existing_parent_abspath;
  svn_boolean_t is_wc_root;
  svn_error_t *err;

  if (svn_path_is_url(path))
    return svn_error_createf(SVN_ERR_ILLEGAL_TARGET, NULL,
                             _("'%s' is not a local path"), path);

  SVN_ERR(svn_dirent_get_absolute(&local_abspath, path, scratch_pool));

  /* See if we're being asked to add a wc-root.  That's typically not
     okay, unless we're in "force" mode.  svn_wc__is_wcroot()
     will return TRUE even if LOCAL_ABSPATH is a *symlink* to a working
     copy root, which is a scenario we want to treat differently.  */
  err = svn_wc__is_wcroot(&is_wc_root, ctx->wc_ctx, local_abspath,
                          scratch_pool);
  if (err)
    {
      if (err->apr_err != SVN_ERR_WC_PATH_NOT_FOUND
          && err->apr_err != SVN_ERR_WC_NOT_WORKING_COPY)
        {
          return svn_error_trace(err);
        }

      svn_error_clear(err);
      err = NULL; /* SVN_NO_ERROR */
      is_wc_root = FALSE;
    }
  if (is_wc_root)
    {
#ifdef HAVE_SYMLINK
      svn_node_kind_t disk_kind;
      svn_boolean_t is_special;

      SVN_ERR(svn_io_check_special_path(local_abspath, &disk_kind, &is_special,
                                        scratch_pool));

      /* A symlink can be an unversioned target and a wcroot. Lets try to add
         the symlink, which can't be a wcroot. */
      if (is_special)
        is_wc_root = FALSE;
      else
#endif
        {
          if (! force)
            return svn_error_createf(
                                 SVN_ERR_ENTRY_EXISTS, NULL,
                                 _("'%s' is already under version control"),
                                 svn_dirent_local_style(local_abspath,
                                                        scratch_pool));
        }
    }

  if (is_wc_root)
    parent_abspath = local_abspath; /* We will only add children */
  else
    parent_abspath = svn_dirent_dirname(local_abspath, scratch_pool);

  existing_parent_abspath = NULL;
  if (add_parents && !is_wc_root)
    {
      apr_pool_t *subpool;
      const char *existing_parent_abspath2;

      subpool = svn_pool_create(scratch_pool);
      SVN_ERR(find_existing_parent(&existing_parent_abspath2, ctx,
                                   parent_abspath, scratch_pool, subpool));
      if (strcmp(existing_parent_abspath2, parent_abspath) != 0)
        existing_parent_abspath = existing_parent_abspath2;
      svn_pool_destroy(subpool);
    }

  SVN_WC__CALL_WITH_WRITE_LOCK(
    add(local_abspath, depth, force, no_ignore, no_autoprops,
        existing_parent_abspath, ctx, scratch_pool),
    ctx->wc_ctx, (existing_parent_abspath ? existing_parent_abspath
                                          : parent_abspath),
    FALSE /* lock_anchor */, scratch_pool);
  return SVN_NO_ERROR;
}