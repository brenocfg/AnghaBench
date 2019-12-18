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
typedef  int /*<<< orphan*/  svn_atomic_t ;
typedef  int /*<<< orphan*/  svn_atomic__str_init_func_t ;
struct TYPE_3__ {char const* errstr; void* baton; int /*<<< orphan*/  str_init_func; } ;
typedef  TYPE_1__ init_baton_t ;

/* Variables and functions */
 scalar_t__ init_once (int /*<<< orphan*/  volatile*,int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  str_init_func_wrapper ; 

const char *
svn_atomic__init_once_no_error(volatile svn_atomic_t *global_status,
                               svn_atomic__str_init_func_t str_init_func,
                               void *baton)
{
  init_baton_t init_baton;
  init_baton.str_init_func = str_init_func;
  init_baton.errstr = NULL;
  init_baton.baton = baton;

  if (init_once(global_status, str_init_func_wrapper, &init_baton))
    return NULL;

  /* Our init function wrapper may not have been called; make sure
     that we return generic error message in that case. */
  if (!init_baton.errstr)
    return "Couldn't perform atomic initialization";
  else
    return init_baton.errstr;
}