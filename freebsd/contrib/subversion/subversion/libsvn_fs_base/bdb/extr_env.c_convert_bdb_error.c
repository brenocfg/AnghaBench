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
struct TYPE_6__ {int /*<<< orphan*/  env; } ;
typedef  TYPE_1__ bdb_env_t ;
struct TYPE_7__ {int /*<<< orphan*/  error_info; TYPE_1__* bdb; int /*<<< orphan*/  env; } ;
typedef  TYPE_2__ bdb_env_baton_t ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_BDB_ERR (TYPE_2__*,int) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  get_error_info (TYPE_1__*) ; 

__attribute__((used)) static svn_error_t *
convert_bdb_error(bdb_env_t *bdb, int db_err)
{
  if (db_err)
    {
      bdb_env_baton_t bdb_baton;
      bdb_baton.env = bdb->env;
      bdb_baton.bdb = bdb;
      bdb_baton.error_info = get_error_info(bdb);
      SVN_BDB_ERR(&bdb_baton, db_err);
    }
  return SVN_NO_ERROR;
}