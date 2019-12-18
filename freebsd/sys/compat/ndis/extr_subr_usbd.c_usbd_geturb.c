#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  union usbd_urb {int dummy; } usbd_urb ;
struct TYPE_3__ {union usbd_urb* isl_arg1; } ;
struct TYPE_4__ {TYPE_1__ isl_others; } ;
struct io_stack_location {TYPE_2__ isl_parameters; } ;
typedef  int /*<<< orphan*/  irp ;

/* Variables and functions */
 struct io_stack_location* IoGetCurrentIrpStackLocation (int /*<<< orphan*/ *) ; 

__attribute__((used)) static union usbd_urb *
usbd_geturb(irp *ip)
{
	struct io_stack_location *irp_sl;

	irp_sl = IoGetCurrentIrpStackLocation(ip);

	return (irp_sl->isl_parameters.isl_others.isl_arg1);
}