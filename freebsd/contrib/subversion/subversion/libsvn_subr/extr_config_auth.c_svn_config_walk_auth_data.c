#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_23__   TYPE_3__ ;
typedef  struct TYPE_22__   TYPE_2__ ;
typedef  struct TYPE_21__   TYPE_1__ ;

/* Type definitions */
struct TYPE_21__ {int /*<<< orphan*/  data; } ;
typedef  TYPE_1__ svn_string_t ;
typedef  int /*<<< orphan*/  svn_stream_t ;
struct TYPE_22__ {scalar_t__ kind; } ;
typedef  TYPE_2__ svn_io_dirent2_t ;
struct TYPE_23__ {scalar_t__ apr_err; } ;
typedef  TYPE_3__ svn_error_t ;
typedef  TYPE_3__* (* svn_config_auth_walk_func_t ) (scalar_t__*,void*,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ;
typedef  scalar_t__ svn_boolean_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;
typedef  int /*<<< orphan*/  apr_hash_t ;
typedef  int /*<<< orphan*/  apr_hash_index_t ;

/* Variables and functions */
 int /*<<< orphan*/  APR_STATUS_IS_ENOENT (scalar_t__) ; 
 scalar_t__ FALSE ; 
 char const* SVN_AUTH_CRED_SIMPLE ; 
 char const* SVN_AUTH_CRED_SSL_CLIENT_CERT ; 
 char const* SVN_AUTH_CRED_SSL_CLIENT_CERT_PW ; 
 char const* SVN_AUTH_CRED_SSL_SERVER_TRUST ; 
 char const* SVN_AUTH_CRED_USERNAME ; 
 int /*<<< orphan*/  SVN_CONFIG_REALMSTRING_KEY ; 
 int /*<<< orphan*/  SVN_ERR (TYPE_3__*) ; 
 scalar_t__ SVN_ERR_CEASE_INVOCATION ; 
 int /*<<< orphan*/  SVN_HASH_TERMINATOR ; 
 TYPE_3__* SVN_NO_ERROR ; 
 int /*<<< orphan*/  SVN__APR_STATUS_IS_ENOTDIR (scalar_t__) ; 
 scalar_t__ TRUE ; 
 int /*<<< orphan*/ * apr_hash_first (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * apr_hash_make (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * apr_hash_next (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  apr_hash_this_key (int /*<<< orphan*/ *) ; 
 TYPE_2__* apr_hash_this_val (int /*<<< orphan*/ *) ; 
 TYPE_3__* svn_auth__file_path (char const**,char const*,char*,char const*,int /*<<< orphan*/ *) ; 
 char* svn_dirent_dirname (char const*,int /*<<< orphan*/ *) ; 
 char* svn_dirent_join (char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_error_clear (TYPE_3__*) ; 
 TYPE_3__* svn_error_compose_create (TYPE_3__*,int /*<<< orphan*/ ) ; 
 TYPE_3__* svn_error_trace (TYPE_3__*) ; 
 TYPE_1__* svn_hash_gets (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 TYPE_3__* svn_hash_read2 (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 TYPE_3__* svn_io_get_dirents3 (int /*<<< orphan*/ **,char const*,scalar_t__,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 TYPE_3__* svn_io_remove_file2 (char const*,scalar_t__,int /*<<< orphan*/ *) ; 
 scalar_t__ svn_node_file ; 
 int /*<<< orphan*/  svn_pool_clear (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_pool_create (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_pool_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_stream_close (int /*<<< orphan*/ *) ; 
 TYPE_3__* svn_stream_open_readonly (int /*<<< orphan*/ **,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

svn_error_t *
svn_config_walk_auth_data(const char *config_dir,
                          svn_config_auth_walk_func_t walk_func,
                          void *walk_baton,
                          apr_pool_t *scratch_pool)
{
  int i;
  apr_pool_t *iterpool;
  svn_boolean_t finished = FALSE;
  const char *cred_kinds[] =
    {
      SVN_AUTH_CRED_SIMPLE,
      SVN_AUTH_CRED_USERNAME,
      SVN_AUTH_CRED_SSL_CLIENT_CERT,
      SVN_AUTH_CRED_SSL_CLIENT_CERT_PW,
      SVN_AUTH_CRED_SSL_SERVER_TRUST,
      NULL
    };

  iterpool = svn_pool_create(scratch_pool);
  for (i = 0; cred_kinds[i]; i++)
    {
      const char *item_path;
      const char *dir_path;
      apr_hash_t *nodes;
      svn_error_t *err;
      apr_pool_t *itempool;
      apr_hash_index_t *hi;

      svn_pool_clear(iterpool);

      if (finished)
        break;

      SVN_ERR(svn_auth__file_path(&item_path, cred_kinds[i], "!", config_dir,
                                  iterpool));

      dir_path = svn_dirent_dirname(item_path, iterpool);

      err = svn_io_get_dirents3(&nodes, dir_path, TRUE, iterpool, iterpool);
      if (err)
        {
          if (!APR_STATUS_IS_ENOENT(err->apr_err)
              && !SVN__APR_STATUS_IS_ENOTDIR(err->apr_err))
            return svn_error_trace(err);

          svn_error_clear(err);
          continue;
        }

      itempool = svn_pool_create(iterpool);
      for (hi = apr_hash_first(iterpool, nodes); hi; hi = apr_hash_next(hi))
        {
          svn_io_dirent2_t *dirent = apr_hash_this_val(hi);
          svn_stream_t *stream;
          apr_hash_t *creds_hash;
          const svn_string_t *realm;
          svn_boolean_t delete_file = FALSE;

          if (finished)
            break;

          if (dirent->kind != svn_node_file)
            continue;

          svn_pool_clear(itempool);

          item_path = svn_dirent_join(dir_path, apr_hash_this_key(hi),
                                      itempool);

          err = svn_stream_open_readonly(&stream, item_path,
                                         itempool, itempool);
          if (err)
            {
              /* Ignore this file. There are no credentials in it anyway */
              svn_error_clear(err);
              continue;
            }

          creds_hash = apr_hash_make(itempool);
          err = svn_hash_read2(creds_hash, stream,
                               SVN_HASH_TERMINATOR, itempool);
          err = svn_error_compose_create(err, svn_stream_close(stream));
          if (err)
            {
              /* Ignore this file. There are no credentials in it anyway */
              svn_error_clear(err);
              continue;
            }

          realm = svn_hash_gets(creds_hash, SVN_CONFIG_REALMSTRING_KEY);
          if (! realm)
            continue; /* Not an auth file */

          err = walk_func(&delete_file, walk_baton, cred_kinds[i],
                          realm->data, creds_hash, itempool);
          if (err && err->apr_err == SVN_ERR_CEASE_INVOCATION)
            {
              svn_error_clear(err);
              err = SVN_NO_ERROR;
              finished = TRUE;
            }
          SVN_ERR(err);

          if (delete_file)
            {
              /* Delete the file on disk */
              SVN_ERR(svn_io_remove_file2(item_path, TRUE, itempool));
            }
        }
    }

  svn_pool_destroy(iterpool);
  return SVN_NO_ERROR;
}