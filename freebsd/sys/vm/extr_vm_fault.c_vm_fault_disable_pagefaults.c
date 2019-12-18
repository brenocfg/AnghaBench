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
 int TDP_NOFAULTING ; 
 int TDP_RESETSPUR ; 
 int curthread_pflags_set (int) ; 

int
vm_fault_disable_pagefaults(void)
{

	return (curthread_pflags_set(TDP_NOFAULTING | TDP_RESETSPUR));
}