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
 int /*<<< orphan*/  CONS_CLRHIST ; 
 int /*<<< orphan*/  err (int,char*) ; 
 int ioctl (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  revert () ; 

__attribute__((used)) static void
clear_history(void)
{
	if (ioctl(0, CONS_CLRHIST) == -1) {
		revert();
		err(1, "clearing history buffer");
	}
}