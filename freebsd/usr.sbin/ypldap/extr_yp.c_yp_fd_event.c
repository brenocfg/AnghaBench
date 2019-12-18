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
 int /*<<< orphan*/  svc_getreq_common (int) ; 
 int /*<<< orphan*/  yp_disable_events () ; 
 int /*<<< orphan*/  yp_enable_events () ; 

void
yp_fd_event(int fd, short event, void *p)
{
	svc_getreq_common(fd);
	yp_disable_events();
	yp_enable_events();
}