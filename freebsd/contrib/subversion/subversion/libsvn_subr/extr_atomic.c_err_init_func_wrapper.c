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
typedef  int svn_boolean_t ;
struct TYPE_3__ {scalar_t__ err; scalar_t__ (* err_init_func ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;int /*<<< orphan*/  pool; int /*<<< orphan*/  baton; } ;
typedef  TYPE_1__ init_baton_t ;

/* Variables and functions */
 scalar_t__ SVN_NO_ERROR ; 
 scalar_t__ stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static svn_boolean_t err_init_func_wrapper(init_baton_t *init_baton)
{
  init_baton->err = init_baton->err_init_func(init_baton->baton,
                                              init_baton->pool);
  return (init_baton->err == SVN_NO_ERROR);
}