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
typedef  int /*<<< orphan*/  svn_sqlite__func_t ;
struct TYPE_4__ {int /*<<< orphan*/  db3; int /*<<< orphan*/  state_pool; } ;
typedef  TYPE_1__ svn_sqlite__db_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  scalar_t__ svn_boolean_t ;
struct function_wrapper_baton_t {void* baton; int /*<<< orphan*/  func; } ;

/* Variables and functions */
 int SQLITE_ANY ; 
 int SQLITE_DETERMINISTIC ; 
 int /*<<< orphan*/  SQLITE_ERR (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 struct function_wrapper_baton_t* apr_pcalloc (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  sqlite3_create_function (int /*<<< orphan*/ ,char const*,int,int,struct function_wrapper_baton_t*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wrapped_func ; 

svn_error_t *
svn_sqlite__create_scalar_function(svn_sqlite__db_t *db,
                                   const char *func_name,
                                   int argc,
                                   svn_boolean_t deterministic,
                                   svn_sqlite__func_t func,
                                   void *baton)
{
  int eTextRep;
  struct function_wrapper_baton_t *fwb = apr_pcalloc(db->state_pool,
                                                     sizeof(*fwb));

  fwb->func = func;
  fwb->baton = baton;

  eTextRep = SQLITE_ANY;
  if (deterministic)
    eTextRep |= SQLITE_DETERMINISTIC;

  SQLITE_ERR(sqlite3_create_function(db->db3, func_name, argc, eTextRep,
                                     fwb, wrapped_func, NULL, NULL),
             db);

  return SVN_NO_ERROR;
}