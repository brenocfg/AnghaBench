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
struct ata_taskfile {scalar_t__ ctl; int /*<<< orphan*/  flags; } ;
struct ata_port {scalar_t__ last_ctl; } ;

/* Variables and functions */
 int /*<<< orphan*/  ATA_TFLAG_DEVICE ; 
 int /*<<< orphan*/  ata_sff_tf_load (struct ata_port*,struct ata_taskfile const*) ; 

__attribute__((used)) static void svia_tf_load(struct ata_port *ap, const struct ata_taskfile *tf)
{
	struct ata_taskfile ttf;

	if (tf->ctl != ap->last_ctl)  {
		ttf = *tf;
		ttf.flags |= ATA_TFLAG_DEVICE;
		tf = &ttf;
	}
	ata_sff_tf_load(ap, tf);
}