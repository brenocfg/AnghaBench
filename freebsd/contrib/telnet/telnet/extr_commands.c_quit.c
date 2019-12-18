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
 int /*<<< orphan*/  Exit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bye ; 
 int /*<<< orphan*/  call (int /*<<< orphan*/ ,char*,char*,int /*<<< orphan*/ ) ; 

void
quit(void)
{
	(void) call(bye, "bye", "fromquit", 0);
	Exit(0);
}