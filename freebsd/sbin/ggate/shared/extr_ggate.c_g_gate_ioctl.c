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
 int /*<<< orphan*/  G_GATE_CTL_NAME ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  g_gate_devfd ; 
 int /*<<< orphan*/  g_gate_xlog (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  getprogname () ; 
 int ioctl (int /*<<< orphan*/ ,unsigned long,void*) ; 
 int /*<<< orphan*/  strerror (int /*<<< orphan*/ ) ; 

void
g_gate_ioctl(unsigned long req, void *data)
{

	if (ioctl(g_gate_devfd, req, data) == -1) {
		g_gate_xlog("%s: ioctl(/dev/%s): %s.", getprogname(),
		    G_GATE_CTL_NAME, strerror(errno));
	}
}