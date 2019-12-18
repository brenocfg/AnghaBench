#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_4__ ;
typedef  struct TYPE_17__   TYPE_3__ ;
typedef  struct TYPE_16__   TYPE_2__ ;
typedef  struct TYPE_15__   TYPE_1__ ;
typedef  struct TYPE_14__   TYPE_11__ ;

/* Type definitions */
struct TYPE_15__ {int /*<<< orphan*/  db_txn; } ;
typedef  TYPE_1__ trail_t ;
struct TYPE_16__ {int /*<<< orphan*/  path; TYPE_4__* fsap_data; } ;
typedef  TYPE_2__ svn_fs_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
struct TYPE_17__ {scalar_t__ kind; } ;
typedef  TYPE_3__ svn_checksum_t ;
struct TYPE_18__ {TYPE_11__* checksum_reps; } ;
typedef  TYPE_4__ base_fs_data_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;
struct TYPE_14__ {int (* get ) (TYPE_11__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* put ) (TYPE_11__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ;} ;
typedef  int /*<<< orphan*/  DBT ;

/* Variables and functions */
 int /*<<< orphan*/  BDB_WRAP (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int DB_NOTFOUND ; 
 int /*<<< orphan*/  N_ (char*) ; 
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SVN_ERR_BAD_CHECKSUM_KIND ; 
 int /*<<< orphan*/  SVN_ERR_FS_ALREADY_EXISTS ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  _ (char*) ; 
 int stub1 (TYPE_11__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (TYPE_11__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ svn_checksum_sha1 ; 
 char* svn_checksum_to_cstring_display (TYPE_3__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_error_create (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * svn_error_createf (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_fs_base__checksum_to_dbt (int /*<<< orphan*/ *,TYPE_3__*) ; 
 int /*<<< orphan*/  svn_fs_base__result_dbt (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_fs_base__str_to_dbt (int /*<<< orphan*/ *,char const*) ; 
 int /*<<< orphan*/  svn_fs_base__track_dbt (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_fs_base__trail_debug (TYPE_1__*,char*,char*) ; 

svn_error_t *svn_fs_bdb__set_checksum_rep(svn_fs_t *fs,
                                          svn_checksum_t *checksum,
                                          const char *rep_key,
                                          trail_t *trail,
                                          apr_pool_t *pool)
{
  base_fs_data_t *bfd = fs->fsap_data;
  DBT key, value;
  int db_err;

  /* We only allow SHA1 checksums in this table. */
  if (checksum->kind != svn_checksum_sha1)
    return svn_error_create(SVN_ERR_BAD_CHECKSUM_KIND, NULL,
                            _("Only SHA1 checksums can be used as keys in the "
                              "checksum-reps table.\n"));

  /* Create a key from our CHECKSUM. */
  svn_fs_base__checksum_to_dbt(&key, checksum);

  /* Check to see if we already have a mapping for CHECKSUM.  If so,
     and the value is the same one we were about to write, that's
     cool -- just do nothing.  If, however, the value is *different*,
     that's a red flag!  */
  svn_fs_base__trail_debug(trail, "checksum-reps", "get");
  db_err = bfd->checksum_reps->get(bfd->checksum_reps, trail->db_txn,
                                   &key, svn_fs_base__result_dbt(&value), 0);
  svn_fs_base__track_dbt(&value, pool);
  if (db_err != DB_NOTFOUND)
    {
      const char *sum_str = svn_checksum_to_cstring_display(checksum, pool);
      return svn_error_createf
        (SVN_ERR_FS_ALREADY_EXISTS, NULL,
         _("Representation key for checksum '%s' exists in filesystem '%s'."),
         sum_str, fs->path);
    }

  /* Create a value from our REP_KEY, and add this record to the table. */
  svn_fs_base__str_to_dbt(&value, rep_key);
  svn_fs_base__trail_debug(trail, "checksum-reps", "put");
  SVN_ERR(BDB_WRAP(fs, N_("storing checksum-reps record"),
                   bfd->checksum_reps->put(bfd->checksum_reps, trail->db_txn,
                                           &key, &value, 0)));
  return SVN_NO_ERROR;
}