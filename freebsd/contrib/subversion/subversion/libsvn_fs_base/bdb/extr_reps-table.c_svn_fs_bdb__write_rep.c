#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_7__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int /*<<< orphan*/  db_txn; } ;
typedef  TYPE_1__ trail_t ;
typedef  int /*<<< orphan*/  svn_skel_t ;
struct TYPE_10__ {TYPE_3__* fsap_data; } ;
typedef  TYPE_2__ svn_fs_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int /*<<< orphan*/  representation_t ;
struct TYPE_11__ {TYPE_7__* representations; int /*<<< orphan*/  format; } ;
typedef  TYPE_3__ base_fs_data_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;
struct TYPE_12__ {int /*<<< orphan*/  (* put ) (TYPE_7__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;
typedef  int /*<<< orphan*/  DBT ;

/* Variables and functions */
 int /*<<< orphan*/ * BDB_WRAP (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  N_ (char*) ; 
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (TYPE_7__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_fs_base__skel_to_dbt (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_fs_base__str_to_dbt (int /*<<< orphan*/ *,char const*) ; 
 int /*<<< orphan*/  svn_fs_base__trail_debug (TYPE_1__*,char*,char*) ; 
 int /*<<< orphan*/  svn_fs_base__unparse_representation_skel (int /*<<< orphan*/ **,int /*<<< orphan*/  const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

svn_error_t *
svn_fs_bdb__write_rep(svn_fs_t *fs,
                      const char *key,
                      const representation_t *rep,
                      trail_t *trail,
                      apr_pool_t *pool)
{
  base_fs_data_t *bfd = fs->fsap_data;
  DBT query, result;
  svn_skel_t *skel;

  /* Convert from native type to skel. */
  SVN_ERR(svn_fs_base__unparse_representation_skel(&skel, rep,
                                                   bfd->format, pool));

  /* Now write the record. */
  svn_fs_base__trail_debug(trail, "representations", "put");
  return BDB_WRAP(fs, N_("storing representation"),
                  bfd->representations->put
                  (bfd->representations, trail->db_txn,
                   svn_fs_base__str_to_dbt(&query, key),
                   svn_fs_base__skel_to_dbt(&result, skel, pool),
                   0));
}