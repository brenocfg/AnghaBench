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
 int /*<<< orphan*/  fileno (int /*<<< orphan*/ ) ; 
 scalar_t__ in_non_blocking_mode ; 
 int /*<<< orphan*/  stdin ; 
 int /*<<< orphan*/  unset_nonblock (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
leave_non_blocking(void)
{
	if (in_non_blocking_mode) {
		unset_nonblock(fileno(stdin));
		in_non_blocking_mode = 0;
	}
}