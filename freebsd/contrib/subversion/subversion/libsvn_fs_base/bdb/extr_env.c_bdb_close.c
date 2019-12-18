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
typedef  int /*<<< orphan*/  svn_error_t ;
struct TYPE_6__ {scalar_t__ pool; TYPE_2__* env; } ;
typedef  TYPE_1__ bdb_env_t ;
struct TYPE_7__ {int (* close ) (TYPE_2__*,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int DB_RUNRECOVERY ; 
 int /*<<< orphan*/  SVN_BDB_AUTO_RECOVER ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/ * convert_bdb_error (TYPE_1__*,int) ; 
 int /*<<< orphan*/  free (TYPE_1__*) ; 
 int stub1 (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * svn_error_trace (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_pool_destroy (scalar_t__) ; 

__attribute__((used)) static svn_error_t *
bdb_close(bdb_env_t *bdb)
{
  svn_error_t *err = SVN_NO_ERROR;

  /* This bit is delcate; we must propagate the error from
     DB_ENV->close to the caller, and always destroy the pool. */
  int db_err = bdb->env->close(bdb->env, 0);

  /* If automatic database recovery is enabled, ignore DB_RUNRECOVERY
     errors, since they're dealt with eventually by BDB itself. */
  if (db_err && (!SVN_BDB_AUTO_RECOVER || db_err != DB_RUNRECOVERY))
    err = convert_bdb_error(bdb, db_err);

  /* Free the environment descriptor. The pool cleanup will do this unless
     the cache has already been destroyed. */
  if (bdb->pool)
    svn_pool_destroy(bdb->pool);
  else
    free(bdb);
  return svn_error_trace(err);
}