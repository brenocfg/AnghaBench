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
typedef  int /*<<< orphan*/  uv_mutex_t ;
struct TYPE_3__ {int /*<<< orphan*/  cond_var; } ;
typedef  TYPE_1__ uv_cond_t ;

/* Variables and functions */
 int /*<<< orphan*/  INFINITE ; 
 int /*<<< orphan*/  SleepConditionVariableCS (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  abort () ; 

void uv_cond_wait(uv_cond_t* cond, uv_mutex_t* mutex) {
  if (!SleepConditionVariableCS(&cond->cond_var, mutex, INFINITE))
    abort();
}