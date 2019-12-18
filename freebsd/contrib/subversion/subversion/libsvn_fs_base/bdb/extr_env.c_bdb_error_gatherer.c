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
typedef  int /*<<< orphan*/  svn_error_t ;
struct TYPE_3__ {int /*<<< orphan*/  (* user_callback ) (int /*<<< orphan*/ *,char*) ;int /*<<< orphan*/ * pending_errors; } ;
typedef  TYPE_1__ bdb_error_info_t ;
typedef  int /*<<< orphan*/  bdb_env_t ;
typedef  int /*<<< orphan*/  DB_ENV ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_BDB_ERROR_GATHERER_IGNORE (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  SVN_ERR_FS_BERKELEY_DB ; 
 TYPE_1__* get_error_info (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  svn_error_compose (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_error_createf (int /*<<< orphan*/ ,int /*<<< orphan*/ *,char*,char const*) ; 

__attribute__((used)) static void
bdb_error_gatherer(const DB_ENV *dbenv, const char *baton, const char *msg)
{
  /* See the documentation at bdb_env_t's definition why the
     (bdb_env_t *) cast is safe and why it is done. */
  bdb_error_info_t *error_info = get_error_info((const bdb_env_t *) baton);
  svn_error_t *new_err;

  SVN_BDB_ERROR_GATHERER_IGNORE(dbenv);

  new_err = svn_error_createf(SVN_ERR_FS_BERKELEY_DB, NULL, "bdb: %s", msg);
  if (error_info->pending_errors)
    svn_error_compose(error_info->pending_errors, new_err);
  else
    error_info->pending_errors = new_err;

  if (error_info->user_callback)
    error_info->user_callback(NULL, (char *)msg); /* ### I hate this cast... */
}