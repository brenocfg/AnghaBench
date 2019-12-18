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
struct kaiocb {int jobflags; } ;

/* Variables and functions */
 int KAIOCB_CLEARED ; 

bool
aio_cancel_cleared(struct kaiocb *job)
{

	/*
	 * The caller should hold the same queue lock held when
	 * aio_clear_cancel_function() was called and set this flag
	 * ensuring this check sees an up-to-date value.  However,
	 * there is no way to assert that.
	 */
	return ((job->jobflags & KAIOCB_CLEARED) != 0);
}