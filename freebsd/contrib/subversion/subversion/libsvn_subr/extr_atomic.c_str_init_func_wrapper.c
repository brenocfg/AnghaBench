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
typedef  int /*<<< orphan*/  svn_boolean_t ;
struct TYPE_3__ {int /*<<< orphan*/ * errstr; int /*<<< orphan*/  baton; int /*<<< orphan*/ * (* str_init_func ) (int /*<<< orphan*/ ) ;} ;
typedef  TYPE_1__ init_baton_t ;

/* Variables and functions */
 int /*<<< orphan*/ * stub1 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static svn_boolean_t str_init_func_wrapper(init_baton_t *init_baton)
{
  init_baton->errstr = init_baton->str_init_func(init_baton->baton);
  return (init_baton->errstr == NULL);
}