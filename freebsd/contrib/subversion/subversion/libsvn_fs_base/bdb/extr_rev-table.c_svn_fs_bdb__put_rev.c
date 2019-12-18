#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_7__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int /*<<< orphan*/  db_txn; } ;
typedef  TYPE_1__ trail_t ;
typedef  int /*<<< orphan*/  svn_skel_t ;
typedef  scalar_t__ svn_revnum_t ;
struct TYPE_11__ {TYPE_3__* fsap_data; } ;
typedef  TYPE_2__ svn_fs_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int /*<<< orphan*/  revision_t ;
typedef  int /*<<< orphan*/  recno ;
typedef  scalar_t__ db_recno_t ;
struct TYPE_12__ {TYPE_7__* revisions; } ;
typedef  TYPE_3__ base_fs_data_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;
struct TYPE_13__ {int (* put ) (TYPE_7__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;
typedef  int /*<<< orphan*/  DBT ;

/* Variables and functions */
 int /*<<< orphan*/ * BDB_WRAP (TYPE_2__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  DB_APPEND ; 
 int /*<<< orphan*/  N_ (char*) ; 
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ *) ; 
 scalar_t__ SVN_IS_VALID_REVNUM (scalar_t__) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int stub1 (TYPE_7__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int stub2 (TYPE_7__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_fs_base__recno_dbt (int /*<<< orphan*/ *,scalar_t__*) ; 
 int /*<<< orphan*/  svn_fs_base__set_dbt (int /*<<< orphan*/ *,scalar_t__*,int) ; 
 int /*<<< orphan*/  svn_fs_base__skel_to_dbt (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_fs_base__trail_debug (TYPE_1__*,char*,char*) ; 
 int /*<<< orphan*/ * svn_fs_base__unparse_revision_skel (int /*<<< orphan*/ **,int /*<<< orphan*/  const*,int /*<<< orphan*/ *) ; 

svn_error_t *
svn_fs_bdb__put_rev(svn_revnum_t *rev,
                    svn_fs_t *fs,
                    const revision_t *revision,
                    trail_t *trail,
                    apr_pool_t *pool)
{
  base_fs_data_t *bfd = fs->fsap_data;
  int db_err;
  db_recno_t recno = 0;
  svn_skel_t *skel;
  DBT key, value;

  /* Convert native type to skel. */
  SVN_ERR(svn_fs_base__unparse_revision_skel(&skel, revision, pool));

  if (SVN_IS_VALID_REVNUM(*rev))
    {
      DBT query, result;

      /* Update the filesystem revision with the new skel. */
      recno = (db_recno_t) *rev + 1;
      svn_fs_base__trail_debug(trail, "revisions", "put");
      db_err = bfd->revisions->put
        (bfd->revisions, trail->db_txn,
         svn_fs_base__set_dbt(&query, &recno, sizeof(recno)),
         svn_fs_base__skel_to_dbt(&result, skel, pool), 0);
      return BDB_WRAP(fs, N_("updating filesystem revision"), db_err);
    }

  svn_fs_base__trail_debug(trail, "revisions", "put");
  db_err = bfd->revisions->put(bfd->revisions, trail->db_txn,
                               svn_fs_base__recno_dbt(&key, &recno),
                               svn_fs_base__skel_to_dbt(&value, skel, pool),
                               DB_APPEND);
  SVN_ERR(BDB_WRAP(fs, N_("storing filesystem revision"), db_err));

  /* Turn the record number into a Subversion revision number.
     Revisions are numbered starting with zero; Berkeley DB record
     numbers begin with one.  */
  *rev = recno - 1;
  return SVN_NO_ERROR;
}