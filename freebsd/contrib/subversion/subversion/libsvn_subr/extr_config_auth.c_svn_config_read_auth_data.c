#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  data; } ;
typedef  TYPE_1__ svn_string_t ;
typedef  int /*<<< orphan*/  svn_stream_t ;
typedef  scalar_t__ svn_node_kind_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;
typedef  int /*<<< orphan*/  apr_hash_t ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_CONFIG_REALMSTRING_KEY ; 
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SVN_ERR_W (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SVN_HASH_TERMINATOR ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/ * apr_hash_make (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  apr_psprintf (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  svn_auth__file_path (char const**,char const*,char const*,char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_dirent_local_style (char const*,int /*<<< orphan*/ *) ; 
 TYPE_1__* svn_hash_gets (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_hash_read2 (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_io_check_path (char const*,scalar_t__*,int /*<<< orphan*/ *) ; 
 scalar_t__ svn_node_file ; 
 int /*<<< orphan*/  svn_stream_close (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_stream_open_readonly (int /*<<< orphan*/ **,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

svn_error_t *
svn_config_read_auth_data(apr_hash_t **hash,
                          const char *cred_kind,
                          const char *realmstring,
                          const char *config_dir,
                          apr_pool_t *pool)
{
  svn_node_kind_t kind;
  const char *auth_path;

  *hash = NULL;

  SVN_ERR(svn_auth__file_path(&auth_path, cred_kind, realmstring, config_dir,
                              pool));
  if (! auth_path)
    return SVN_NO_ERROR;

  SVN_ERR(svn_io_check_path(auth_path, &kind, pool));
  if (kind == svn_node_file)
    {
      svn_stream_t *stream;
      svn_string_t *stored_realm;

      SVN_ERR_W(svn_stream_open_readonly(&stream, auth_path, pool, pool),
                _("Unable to open auth file for reading"));

      *hash = apr_hash_make(pool);

      SVN_ERR_W(svn_hash_read2(*hash, stream, SVN_HASH_TERMINATOR, pool),
                apr_psprintf(pool, _("Error parsing '%s'"),
                             svn_dirent_local_style(auth_path, pool)));

      stored_realm = svn_hash_gets(*hash, SVN_CONFIG_REALMSTRING_KEY);

      if (!stored_realm || strcmp(stored_realm->data, realmstring) != 0)
        *hash = NULL; /* Hash collision, or somebody tampering with storage */

      SVN_ERR(svn_stream_close(stream));
    }

  return SVN_NO_ERROR;
}