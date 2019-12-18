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

/* Variables and functions */
 int __sys_thr_kill (long,int) ; 
 int __sys_thr_self (long*) ; 

int
__raise(int s)
{
	long id;

	if (__sys_thr_self(&id) == -1)
		return (-1);
	return (__sys_thr_kill(id, s));
}