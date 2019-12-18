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
 int /*<<< orphan*/  ThreadLock () ; 
 int /*<<< orphan*/  ThreadUnlock () ; 
 int nodelistsize ; 

int NodeListSize(void)
{
	int size;

	ThreadLock();
	size = nodelistsize;
	ThreadUnlock();

	return size;
}