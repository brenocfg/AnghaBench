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
struct _IOCTL_ARG {scalar_t__ ioctl_cmnd; } ;

/* Variables and functions */
 int /*<<< orphan*/  wakeup (struct _IOCTL_ARG*) ; 

__attribute__((used)) static void hpt_ioctl_done(struct _IOCTL_ARG *arg)
{
	arg->ioctl_cmnd = 0;
	wakeup(arg);
}