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
struct TYPE_3__ {int /*<<< orphan*/ * context; } ;
typedef  TYPE_1__ svn_sqlite__context_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
struct function_wrapper_baton_t {int /*<<< orphan*/  baton; int /*<<< orphan*/ * (* func ) (TYPE_1__*,int,void*,int /*<<< orphan*/ ) ;} ;
typedef  int /*<<< orphan*/  sqlite3_value ;
typedef  int /*<<< orphan*/  sqlite3_context ;
typedef  int /*<<< orphan*/  buf ;

/* Variables and functions */
 int /*<<< orphan*/  sqlite3_result_error (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 struct function_wrapper_baton_t* sqlite3_user_data (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * stub1 (TYPE_1__*,int,void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_err_best_message (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  svn_error_clear (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
wrapped_func(sqlite3_context *context,
             int argc,
             sqlite3_value *values[])
{
  struct function_wrapper_baton_t *fwb = sqlite3_user_data(context);
  svn_sqlite__context_t sctx;
  svn_error_t *err;
  void *void_values = values;

  sctx.context = context;

  err = fwb->func(&sctx, argc, void_values, fwb->baton);

  if (err)
    {
      char buf[256];
      sqlite3_result_error(context,
                           svn_err_best_message(err, buf, sizeof(buf)),
                           -1);
      svn_error_clear(err);
    }
}