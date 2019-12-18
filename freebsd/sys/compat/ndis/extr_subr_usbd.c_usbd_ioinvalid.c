#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct io_stack_location {int /*<<< orphan*/  isl_minor; int /*<<< orphan*/  isl_major; } ;
struct TYPE_8__ {scalar_t__ isb_info; int /*<<< orphan*/  isb_status; } ;
struct TYPE_9__ {TYPE_1__ irp_iostat; } ;
typedef  TYPE_2__ irp ;
typedef  int /*<<< orphan*/  int32_t ;
typedef  int /*<<< orphan*/  device_t ;
struct TYPE_10__ {int /*<<< orphan*/  do_devext; } ;
typedef  TYPE_3__ device_object ;

/* Variables and functions */
 int /*<<< orphan*/  IO_NO_INCREMENT ; 
 int /*<<< orphan*/  IoCompleteRequest (TYPE_2__*,int /*<<< orphan*/ ) ; 
 struct io_stack_location* IoGetCurrentIrpStackLocation (TYPE_2__*) ; 
 int /*<<< orphan*/  STATUS_FAILURE ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int32_t
usbd_ioinvalid(device_object *dobj, irp *ip)
{
	device_t dev = dobj->do_devext;
	struct io_stack_location *irp_sl;

	irp_sl = IoGetCurrentIrpStackLocation(ip);
	device_printf(dev, "invalid I/O dispatch %d:%d\n", irp_sl->isl_major,
	    irp_sl->isl_minor);

	ip->irp_iostat.isb_status = STATUS_FAILURE;
	ip->irp_iostat.isb_info = 0;

	IoCompleteRequest(ip, IO_NO_INCREMENT);

	return (STATUS_FAILURE);
}