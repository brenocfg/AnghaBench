#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  data; int /*<<< orphan*/  len; } ;
typedef  TYPE_1__ svn_string_t ;
typedef  int /*<<< orphan*/  svn_revnum_t ;
typedef  int /*<<< orphan*/  svn_fs_x__batch_fsync_t ;
struct TYPE_8__ {int /*<<< orphan*/  fs; } ;
typedef  TYPE_2__ svn_fs_txn_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;
typedef  int /*<<< orphan*/  apr_hash_t ;
typedef  int /*<<< orphan*/  apr_file_t ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SVN_FS__PROP_TXN_CHECK_LOCKS ; 
 int /*<<< orphan*/  SVN_FS__PROP_TXN_CHECK_OOD ; 
 int /*<<< orphan*/  SVN_FS__PROP_TXN_CLIENT_DATE ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  SVN_PROP_REVISION_DATE ; 
 int /*<<< orphan*/  apr_time_now () ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  strlen (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_fs_x__batch_fsync_open_file (int /*<<< orphan*/ **,int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ *) ; 
 char* svn_fs_x__path_revprops (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_fs_x__txn_proplist (int /*<<< orphan*/ **,TYPE_2__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_fs_x__write_non_packed_revprops (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 TYPE_1__* svn_hash_gets (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_hash_sets (int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  svn_time_to_cstring (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static svn_error_t *
write_final_revprop(const char **path,
                    svn_fs_txn_t *txn,
                    svn_revnum_t revision,
                    svn_fs_x__batch_fsync_t *batch,
                    apr_pool_t *result_pool,
                    apr_pool_t *scratch_pool)
{
  apr_hash_t *props;
  svn_string_t date;
  svn_string_t *client_date;
  apr_file_t *file;

  SVN_ERR(svn_fs_x__txn_proplist(&props, txn, scratch_pool));

  /* Remove any temporary txn props representing 'flags'. */
  if (svn_hash_gets(props, SVN_FS__PROP_TXN_CHECK_OOD))
    svn_hash_sets(props, SVN_FS__PROP_TXN_CHECK_OOD, NULL);

  if (svn_hash_gets(props, SVN_FS__PROP_TXN_CHECK_LOCKS))
    svn_hash_sets(props, SVN_FS__PROP_TXN_CHECK_LOCKS, NULL);

  client_date = svn_hash_gets(props, SVN_FS__PROP_TXN_CLIENT_DATE);
  if (client_date)
    svn_hash_sets(props, SVN_FS__PROP_TXN_CLIENT_DATE, NULL);

  /* Update commit time to ensure that svn:date revprops remain ordered if
     requested. */
  if (!client_date || strcmp(client_date->data, "1"))
    {
      date.data = svn_time_to_cstring(apr_time_now(), scratch_pool);
      date.len = strlen(date.data);
      svn_hash_sets(props, SVN_PROP_REVISION_DATE, &date);
    }

  /* Create a file at the final revprops location. */
  *path = svn_fs_x__path_revprops(txn->fs, revision, result_pool);
  SVN_ERR(svn_fs_x__batch_fsync_open_file(&file, batch, *path, scratch_pool));

  /* Write the new contents to the final revprops file. */
  SVN_ERR(svn_fs_x__write_non_packed_revprops(file, props, scratch_pool));

  return SVN_NO_ERROR;
}