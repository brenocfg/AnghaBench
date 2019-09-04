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
 int /*<<< orphan*/  Error (char*) ; 
 size_t NODESTACKSIZE ; 
 int* nodestack ; 
 int* nodestackptr ; 
 int /*<<< orphan*/  nodestacksize ; 

void Q2_PushNodeStack(int num)
{
	*nodestackptr = num;
	nodestackptr++;
	nodestacksize++;
	//
	if (nodestackptr >= &nodestack[NODESTACKSIZE])
	{
		Error("Q2_PushNodeStack: stack overflow\n");
	} //end if
}