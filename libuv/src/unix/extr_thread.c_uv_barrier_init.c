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
typedef  int /*<<< orphan*/  uv_barrier_t ;

/* Variables and functions */
 int UV__ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pthread_barrier_init (int /*<<< orphan*/ *,int /*<<< orphan*/ *,unsigned int) ; 

int uv_barrier_init(uv_barrier_t* barrier, unsigned int count) {
  return UV__ERR(pthread_barrier_init(barrier, NULL, count));
}