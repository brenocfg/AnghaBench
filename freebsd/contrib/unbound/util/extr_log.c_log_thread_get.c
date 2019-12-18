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
 int /*<<< orphan*/  key_created ; 
 int /*<<< orphan*/  logkey ; 
 scalar_t__ ub_thread_key_get (int /*<<< orphan*/ ) ; 

int log_thread_get(void)
{
	unsigned int* tid;
	if(!key_created) return 0;
	tid = (unsigned int*)ub_thread_key_get(logkey);
	return (int)(tid?*tid:0);
}