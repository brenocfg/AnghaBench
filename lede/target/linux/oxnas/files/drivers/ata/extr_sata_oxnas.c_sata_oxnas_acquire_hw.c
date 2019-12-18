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
struct ata_port {int /*<<< orphan*/  port_no; int /*<<< orphan*/  host; } ;

/* Variables and functions */
 scalar_t__ HW_LOCKER_UID ; 
 int /*<<< orphan*/  SATA_SCSI_STACK ; 
 int __acquire_sata_core (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int,int,void*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int sata_oxnas_acquire_hw(
	struct ata_port *ap,
	int may_sleep,
	int timeout_jiffies)
{
	return __acquire_sata_core(ap->host, ap->port_no, NULL, 0, may_sleep,
				   timeout_jiffies, 1, (void *)HW_LOCKER_UID,
				   SATA_SCSI_STACK);
}