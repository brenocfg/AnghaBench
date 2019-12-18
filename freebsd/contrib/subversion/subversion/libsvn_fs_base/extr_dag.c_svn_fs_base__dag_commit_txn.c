#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  trail_t ;
struct TYPE_8__ {int /*<<< orphan*/  data; int /*<<< orphan*/  len; } ;
typedef  TYPE_1__ svn_string_t ;
typedef  int /*<<< orphan*/  svn_revnum_t ;
struct TYPE_9__ {char* id; int /*<<< orphan*/ * fs; } ;
typedef  TYPE_2__ svn_fs_txn_t ;
typedef  int /*<<< orphan*/  svn_fs_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
struct TYPE_10__ {char const* txn_id; } ;
typedef  TYPE_3__ revision_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;
typedef  int /*<<< orphan*/  apr_hash_t ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SVN_FS__PROP_TXN_CHECK_LOCKS ; 
 int /*<<< orphan*/  SVN_FS__PROP_TXN_CHECK_OOD ; 
 int /*<<< orphan*/  SVN_FS__PROP_TXN_CLIENT_DATE ; 
 int /*<<< orphan*/  SVN_INVALID_REVNUM ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  SVN_PROP_REVISION_DATE ; 
 int /*<<< orphan*/  apr_time_now () ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  strlen (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_fs_base__set_rev_prop (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_fs_base__set_txn_prop (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_fs_base__txn_make_committed (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_fs_base__txn_proplist_in_trail (int /*<<< orphan*/ **,char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_fs_bdb__put_rev (int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_3__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 TYPE_1__* svn_hash_gets (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_time_to_cstring (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

svn_error_t *
svn_fs_base__dag_commit_txn(svn_revnum_t *new_rev,
                            svn_fs_txn_t *txn,
                            trail_t *trail,
                            apr_pool_t *pool)
{
  revision_t revision;
  apr_hash_t *txnprops;
  svn_fs_t *fs = txn->fs;
  const char *txn_id = txn->id;
  const svn_string_t *client_date;

  /* Remove any temporary transaction properties initially created by
     begin_txn().  */
  SVN_ERR(svn_fs_base__txn_proplist_in_trail(&txnprops, txn_id, trail));

  /* Add new revision entry to `revisions' table. */
  revision.txn_id = txn_id;
  *new_rev = SVN_INVALID_REVNUM;
  SVN_ERR(svn_fs_bdb__put_rev(new_rev, fs, &revision, trail, pool));

  if (svn_hash_gets(txnprops, SVN_FS__PROP_TXN_CHECK_OOD))
    SVN_ERR(svn_fs_base__set_txn_prop
            (fs, txn_id, SVN_FS__PROP_TXN_CHECK_OOD, NULL, trail, pool));

  if (svn_hash_gets(txnprops, SVN_FS__PROP_TXN_CHECK_LOCKS))
    SVN_ERR(svn_fs_base__set_txn_prop
            (fs, txn_id, SVN_FS__PROP_TXN_CHECK_LOCKS, NULL, trail, pool));

  client_date = svn_hash_gets(txnprops, SVN_FS__PROP_TXN_CLIENT_DATE);
  if (client_date)
    SVN_ERR(svn_fs_base__set_txn_prop
            (fs, txn_id, SVN_FS__PROP_TXN_CLIENT_DATE, NULL, trail, pool));

  /* Promote the unfinished transaction to a committed one. */
  SVN_ERR(svn_fs_base__txn_make_committed(fs, txn_id, *new_rev,
                                          trail, pool));

  if (!client_date || strcmp(client_date->data, "1"))
    {
      /* Set a date on the commit if requested.  We wait until now to fetch the
         date, so it's definitely newer than any previous revision's date. */
      svn_string_t date;
      date.data = svn_time_to_cstring(apr_time_now(), pool);
      date.len = strlen(date.data);
      SVN_ERR(svn_fs_base__set_rev_prop(fs, *new_rev, SVN_PROP_REVISION_DATE,
                                        NULL, &date, trail, pool));
    }

  return SVN_NO_ERROR;
}