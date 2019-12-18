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
struct cam_ed {int /*<<< orphan*/  inq_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  scsi_print_inquiry (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
scsi_proto_announce(struct cam_ed *device)
{
	scsi_print_inquiry(&device->inq_data);
}