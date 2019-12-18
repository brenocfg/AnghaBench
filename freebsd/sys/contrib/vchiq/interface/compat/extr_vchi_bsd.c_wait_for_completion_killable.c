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
struct completion {int dummy; } ;

/* Variables and functions */
 int wait_for_completion_interruptible (struct completion*) ; 

int
wait_for_completion_killable(struct completion *c)
{

	return wait_for_completion_interruptible(c);
}