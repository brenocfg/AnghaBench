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
struct TYPE_4__ {int /*<<< orphan*/  sdb; } ;
typedef  TYPE_1__ svn_wc__db_wcroot_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
struct with_triggers_baton_t {int /*<<< orphan*/  drop_trigger; int /*<<< orphan*/  cb_baton; int /*<<< orphan*/ * (* cb_func ) (int /*<<< orphan*/ ,TYPE_1__*,char const*,int /*<<< orphan*/ *) ;int /*<<< orphan*/  create_trigger; } ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * stub1 (int /*<<< orphan*/ ,TYPE_1__*,char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_error_compose_create (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_error_trace (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * svn_sqlite__exec_statements (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static svn_error_t *
with_triggers(void *baton,
              svn_wc__db_wcroot_t *wcroot,
              const char *local_relpath,
              apr_pool_t *scratch_pool)
{
  struct with_triggers_baton_t *b = baton;
  svn_error_t *err1;
  svn_error_t *err2;

  SVN_ERR(svn_sqlite__exec_statements(wcroot->sdb, b->create_trigger));

  err1 = b->cb_func(b->cb_baton, wcroot, local_relpath, scratch_pool);

  err2 = svn_sqlite__exec_statements(wcroot->sdb, b->drop_trigger);

  return svn_error_trace(svn_error_compose_create(err1, err2));
}