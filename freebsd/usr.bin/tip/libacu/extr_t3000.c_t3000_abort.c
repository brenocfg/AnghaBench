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
 int /*<<< orphan*/  FD ; 
 int /*<<< orphan*/  t3000_disconnect () ; 
 int /*<<< orphan*/  t3000_write (int /*<<< orphan*/ ,char*,int) ; 

void
t3000_abort(void)
{
	t3000_write(FD, "\r", 1);	/* send anything to abort the call */
	t3000_disconnect();
}