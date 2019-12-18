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
 int /*<<< orphan*/  API_GET_TIMER ; 
 int /*<<< orphan*/  syscall (int /*<<< orphan*/ ,int /*<<< orphan*/ *,unsigned long*,unsigned long*) ; 

unsigned long
ub_get_timer(unsigned long base)
{
	unsigned long cur;

	if (!syscall(API_GET_TIMER, NULL, &cur, &base))
		return (0);

	return (cur);
}