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
typedef  int /*<<< orphan*/  mtx_t ;

/* Variables and functions */
#define  EBUSY 128 
 int pthread_mutex_trylock (int /*<<< orphan*/ *) ; 
 int thrd_busy ; 
 int thrd_error ; 
 int thrd_success ; 

int
mtx_trylock(mtx_t *mtx)
{

	switch (pthread_mutex_trylock(mtx)) {
	case 0:
		return (thrd_success);
	case EBUSY:
		return (thrd_busy);
	default:
		return (thrd_error);
	}
}