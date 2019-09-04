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
 int UV__ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pthread_rwlock_init (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

int uv_rwlock_init(uv_rwlock_t* rwlock) {
  return UV__ERR(pthread_rwlock_init(rwlock, NULL));
}