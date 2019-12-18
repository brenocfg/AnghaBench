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
struct ifnet {void* if_ioctl; } ;
typedef  scalar_t__ if_t ;

/* Variables and functions */

void
if_setioctlfn(if_t ifp, int (*ioctl_fn)(if_t, u_long, caddr_t))
{
	((struct ifnet *)ifp)->if_ioctl = (void *)ioctl_fn;
}