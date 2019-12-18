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
typedef  int /*<<< orphan*/  sem_t ;

/* Variables and functions */
 int _libc_sem_getvalue_compat (int /*<<< orphan*/ *,int*) ; 

int
_sem_getvalue_compat(sem_t * __restrict sem, int * __restrict sval)
{
	return _libc_sem_getvalue_compat(sem, sval);
}