#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  data; int /*<<< orphan*/  len; } ;
typedef  TYPE_1__ svn_string_t ;
typedef  int /*<<< orphan*/  svn_stream_t ;
typedef  int /*<<< orphan*/  svn_fs_txn_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  scalar_t__ svn_boolean_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;
typedef  int /*<<< orphan*/  apr_hash_t ;
typedef  int /*<<< orphan*/  apr_file_t ;

/* Variables and functions */
 int APR_BUFFERED ; 
 int APR_CREATE ; 
 int /*<<< orphan*/  APR_OS_DEFAULT ; 
 int APR_TRUNCATE ; 
 int APR_WRITE ; 
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SVN_FS__PROP_TXN_CHECK_LOCKS ; 
 int /*<<< orphan*/  SVN_FS__PROP_TXN_CHECK_OOD ; 
 int /*<<< orphan*/  SVN_FS__PROP_TXN_CLIENT_DATE ; 
 int /*<<< orphan*/  SVN_HASH_TERMINATOR ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  SVN_PROP_REVISION_DATE ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  apr_time_now () ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  strlen (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_fs_fs__txn_proplist (int /*<<< orphan*/ **,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 TYPE_1__* svn_hash_gets (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_hash_sets (int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  svn_hash_write2 (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_io_copy_perms (char const*,char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_io_file_close (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_io_file_flush_to_disk (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_io_file_open (int /*<<< orphan*/ **,char const*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_stream_close (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_stream_from_aprfile2 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_time_to_cstring (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static svn_error_t *
write_final_revprop(const char *path,
                    const char *perms_reference,
                    svn_fs_txn_t *txn,
                    svn_boolean_t flush_to_disk,
                    apr_pool_t *pool)
{
  apr_hash_t *txnprops;
  svn_string_t date;
  svn_string_t *client_date;
  apr_file_t *revprop_file;
  svn_stream_t *stream;

  SVN_ERR(svn_fs_fs__txn_proplist(&txnprops, txn, pool));

  /* Remove any temporary txn props representing 'flags'. */
  svn_hash_sets(txnprops, SVN_FS__PROP_TXN_CHECK_OOD, NULL);
  svn_hash_sets(txnprops, SVN_FS__PROP_TXN_CHECK_LOCKS, NULL);

  client_date = svn_hash_gets(txnprops, SVN_FS__PROP_TXN_CLIENT_DATE);
  if (client_date)
    {
      svn_hash_sets(txnprops, SVN_FS__PROP_TXN_CLIENT_DATE, NULL);
    }

  /* Update commit time to ensure that svn:date revprops remain ordered if
     requested. */
  if (!client_date || strcmp(client_date->data, "1"))
    {
      date.data = svn_time_to_cstring(apr_time_now(), pool);
      date.len = strlen(date.data);
      svn_hash_sets(txnprops, SVN_PROP_REVISION_DATE, &date);
    }

  /* Create new revprops file. Tell OS to truncate existing file,
     since  file may already exists from failed transaction. */
  SVN_ERR(svn_io_file_open(&revprop_file, path,
                           APR_WRITE | APR_CREATE | APR_TRUNCATE
                           | APR_BUFFERED, APR_OS_DEFAULT, pool));

  stream = svn_stream_from_aprfile2(revprop_file, TRUE, pool);
  SVN_ERR(svn_hash_write2(txnprops, stream, SVN_HASH_TERMINATOR, pool));
  SVN_ERR(svn_stream_close(stream));

  if (flush_to_disk)
    SVN_ERR(svn_io_file_flush_to_disk(revprop_file, pool));
  SVN_ERR(svn_io_file_close(revprop_file, pool));

  SVN_ERR(svn_io_copy_perms(perms_reference, path, pool));

  return SVN_NO_ERROR;
}