#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  uv_rwlock_t ;

/* Variables and functions */
 int /*<<< orphan*/  abort () ; 
 scalar_t__ pthread_rwlock_unlock (int /*<<< orphan*/ *) ; 

void uv_rwlock_wrunlock(uv_rwlock_t* rwlock) {
  if (pthread_rwlock_unlock(rwlock))
    abort();
}