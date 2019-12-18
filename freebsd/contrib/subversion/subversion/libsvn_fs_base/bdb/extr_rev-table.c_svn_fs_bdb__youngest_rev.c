#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_8__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int /*<<< orphan*/  db_txn; } ;
typedef  TYPE_1__ trail_t ;
typedef  scalar_t__ svn_revnum_t ;
struct TYPE_11__ {int /*<<< orphan*/  path; TYPE_3__* fsap_data; } ;
typedef  TYPE_2__ svn_fs_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  scalar_t__ db_recno_t ;
struct TYPE_12__ {TYPE_8__* revisions; } ;
typedef  TYPE_3__ base_fs_data_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;
struct TYPE_13__ {int (* cursor ) (TYPE_8__*,int /*<<< orphan*/ ,int /*<<< orphan*/ **,int /*<<< orphan*/ ) ;} ;
typedef  int /*<<< orphan*/  DBT ;
typedef  int /*<<< orphan*/  DBC ;

/* Variables and functions */
 int /*<<< orphan*/  BDB_WRAP (TYPE_2__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  DB_LAST ; 
 int DB_NOTFOUND ; 
 int /*<<< orphan*/  N_ (char*) ; 
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SVN_ERR_FS_CORRUPT ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  TRUE ; 
 int stub1 (TYPE_8__*,int /*<<< orphan*/ ,int /*<<< orphan*/ **,int /*<<< orphan*/ ) ; 
 int svn_bdb_dbc_close (int /*<<< orphan*/ *) ; 
 int svn_bdb_dbc_get (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * svn_error_createf (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_fs__check_fs (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_fs_base__nodata_dbt (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_fs_base__recno_dbt (int /*<<< orphan*/ *,scalar_t__*) ; 
 int /*<<< orphan*/  svn_fs_base__trail_debug (TYPE_1__*,char*,char*) ; 

svn_error_t *
svn_fs_bdb__youngest_rev(svn_revnum_t *youngest_p,
                         svn_fs_t *fs,
                         trail_t *trail,
                         apr_pool_t *pool)
{
  base_fs_data_t *bfd = fs->fsap_data;
  int db_err;
  DBC *cursor = 0;
  DBT key, value;
  db_recno_t recno;

  SVN_ERR(svn_fs__check_fs(fs, TRUE));

  /* Create a database cursor.  */
  svn_fs_base__trail_debug(trail, "revisions", "cursor");
  SVN_ERR(BDB_WRAP(fs, N_("getting youngest revision (creating cursor)"),
                   bfd->revisions->cursor(bfd->revisions, trail->db_txn,
                                          &cursor, 0)));

  /* Find the last entry in the `revisions' table.  */
  db_err = svn_bdb_dbc_get(cursor,
                           svn_fs_base__recno_dbt(&key, &recno),
                           svn_fs_base__nodata_dbt(&value),
                           DB_LAST);

  if (db_err)
    {
      /* Free the cursor.  Ignore any error value --- the error above
         is more interesting.  */
      svn_bdb_dbc_close(cursor);

      if (db_err == DB_NOTFOUND)
        /* The revision 0 should always be present, at least.  */
        return
          svn_error_createf
          (SVN_ERR_FS_CORRUPT, 0,
           "Corrupt DB: revision 0 missing from 'revisions' table, in "
           "filesystem '%s'", fs->path);

      SVN_ERR(BDB_WRAP(fs, N_("getting youngest revision (finding last entry)"),
                       db_err));
    }

  /* You can't commit a transaction with open cursors, because:
     1) key/value pairs don't get deleted until the cursors referring
     to them are closed, so closing a cursor can fail for various
     reasons, and txn_commit shouldn't fail that way, and
     2) using a cursor after committing its transaction can cause
     undetectable database corruption.  */
  SVN_ERR(BDB_WRAP(fs, N_("getting youngest revision (closing cursor)"),
                   svn_bdb_dbc_close(cursor)));

  /* Turn the record number into a Subversion revision number.
     Revisions are numbered starting with zero; Berkeley DB record
     numbers begin with one.  */
  *youngest_p = recno - 1;
  return SVN_NO_ERROR;
}