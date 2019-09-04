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
 int* nodestack ; 
 int* nodestackptr ; 
 int /*<<< orphan*/  nodestacksize ; 

int Q2_PopNodeStack(void)
{
	//if the stack is empty
	if (nodestackptr <= nodestack) return -1;
	//decrease stack pointer
	nodestackptr--;
	nodestacksize--;
	//return the top value from the stack
	return *nodestackptr;
}