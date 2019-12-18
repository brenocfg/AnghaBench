#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  events; } ;

/* Variables and functions */
 int /*<<< orphan*/  POLLOUT ; 
 TYPE_1__ kernel_pollfd ; 
 int poll (TYPE_1__*,int,int) ; 

int ubd_write_poll(int timeout)
{
	kernel_pollfd.events = POLLOUT;
	return poll(&kernel_pollfd, 1, timeout);
}