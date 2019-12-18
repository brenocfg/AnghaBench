#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {scalar_t__ val; scalar_t__ max; scalar_t__ countdown; int /*<<< orphan*/  mut; int /*<<< orphan*/  cond; } ;
typedef  TYPE_1__ poolTest_t ;

/* Variables and functions */
 int /*<<< orphan*/  UTIL_sleepMilli (int) ; 
 int /*<<< orphan*/  ZSTD_pthread_cond_signal (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ZSTD_pthread_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ZSTD_pthread_mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void waitLongFn(void *opaque) {
  poolTest_t* const test = (poolTest_t*) opaque;
  ZSTD_pthread_mutex_lock(&test->mut);
  test->val++;
  if (test->val > test->max)
      test->max = test->val;
  ZSTD_pthread_mutex_unlock(&test->mut);

  UTIL_sleepMilli(10);

  ZSTD_pthread_mutex_lock(&test->mut);
  test->val--;
  test->countdown--;
  if (test->countdown == 0)
      ZSTD_pthread_cond_signal(&test->cond);
  ZSTD_pthread_mutex_unlock(&test->mut);
}