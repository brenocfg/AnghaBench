#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  svn_node_kind_t ;
typedef  int /*<<< orphan*/  svn_magic__cookie_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
struct TYPE_5__ {int /*<<< orphan*/  notify_baton2; int /*<<< orphan*/  notify_func2; int /*<<< orphan*/  wc_ctx; } ;
typedef  TYPE_1__ svn_client_ctx_t ;
typedef  scalar_t__ svn_boolean_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;
typedef  int /*<<< orphan*/  apr_hash_t ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  SVN_PROP_BOOLEAN_TRUE ; 
 int /*<<< orphan*/  SVN_PROP_SPECIAL ; 
 int /*<<< orphan*/ * apr_hash_make (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_client__get_all_auto_props (int /*<<< orphan*/ **,int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_client__get_paths_auto_props (int /*<<< orphan*/ **,char const**,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_dirent_dirname (char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_hash_sets (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_io_check_special_path (char const*,int /*<<< orphan*/ *,scalar_t__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_string_create (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_wc_add_from_disk3 (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static svn_error_t *
add_file(const char *local_abspath,
         svn_magic__cookie_t *magic_cookie,
         apr_hash_t *autoprops,
         svn_boolean_t no_autoprops,
         svn_client_ctx_t *ctx,
         apr_pool_t *pool)
{
  apr_hash_t *properties;
  const char *mimetype;
  svn_node_kind_t kind;
  svn_boolean_t is_special;

  /* Check to see if this is a special file. */
  SVN_ERR(svn_io_check_special_path(local_abspath, &kind, &is_special, pool));

  /* Determine the properties that the file should have */
  if (is_special)
    {
      mimetype = NULL;
      properties = apr_hash_make(pool);
      svn_hash_sets(properties, SVN_PROP_SPECIAL,
                    svn_string_create(SVN_PROP_BOOLEAN_TRUE, pool));
    }
  else
    {
      apr_hash_t *file_autoprops = NULL;

      /* Get automatic properties */
      /* If we are setting autoprops grab the inherited svn:auto-props and
         config file auto-props for this file if we haven't already got them
         when iterating over the file's unversioned parents. */
      if (!no_autoprops)
        {
          if (autoprops == NULL)
            SVN_ERR(svn_client__get_all_auto_props(
              &file_autoprops, svn_dirent_dirname(local_abspath,pool),
              ctx, pool, pool));
          else
            file_autoprops = autoprops;
        }

      /* This may fail on write-only files:
         we open them to estimate file type. */
      SVN_ERR(svn_client__get_paths_auto_props(&properties, &mimetype,
                                               local_abspath, magic_cookie,
                                               file_autoprops, ctx, pool,
                                               pool));
    }

  /* Add the file */
  SVN_ERR(svn_wc_add_from_disk3(ctx->wc_ctx, local_abspath, properties,
                                FALSE /* skip checks */,
                                ctx->notify_func2, ctx->notify_baton2, pool));

  return SVN_NO_ERROR;
}