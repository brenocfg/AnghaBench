#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u_int32_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
struct TYPE_6__ {int /*<<< orphan*/  pool; int /*<<< orphan*/  path; int /*<<< orphan*/  dbconfig_file; int /*<<< orphan*/  key; TYPE_2__* env; int /*<<< orphan*/  path_bdb; } ;
typedef  TYPE_1__ bdb_env_t ;
struct TYPE_7__ {int /*<<< orphan*/  (* set_flags ) (TYPE_2__*,int /*<<< orphan*/ ,int) ;int /*<<< orphan*/  (* open ) (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  DB_THREAD ; 
 int /*<<< orphan*/  SVN_BDB_AUTO_COMMIT ; 
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * bdb_cache_key (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  convert_bdb_error (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub2 (TYPE_2__*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static svn_error_t *
bdb_open(bdb_env_t *bdb, u_int32_t flags, int mode)
{
#if APR_HAS_THREADS
  flags |= DB_THREAD;
#endif
  SVN_ERR(convert_bdb_error
          (bdb, (bdb->env->open)(bdb->env, bdb->path_bdb, flags, mode)));

#if SVN_BDB_AUTO_COMMIT
  /* Assert the BDB_AUTO_COMMIT flag on the opened environment. This
     will force all operations on the environment (and handles that
     are opened within the environment) to be transactional. */

  SVN_ERR(convert_bdb_error
          (bdb, bdb->env->set_flags(bdb->env, SVN_BDB_AUTO_COMMIT, 1)));
#endif

  return bdb_cache_key(&bdb->key, &bdb->dbconfig_file,
                       bdb->path, bdb->pool);
}