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
struct completion {scalar_t__ done; } ;

/* Variables and functions */
 int /*<<< orphan*/  sleepq_lock (struct completion*) ; 
 int /*<<< orphan*/  sleepq_release (struct completion*) ; 

int
linux_completion_done(struct completion *c)
{
	int isdone;

	sleepq_lock(c);
	isdone = (c->done != 0);
	sleepq_release(c);
	return (isdone);
}