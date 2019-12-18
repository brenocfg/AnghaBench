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
struct ata_taskfile {scalar_t__ protocol; } ;
struct ata_port {int dummy; } ;

/* Variables and functions */
 scalar_t__ ATAPI_PROT_DMA ; 
 scalar_t__ ATA_PROT_DMA ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  ata_sff_tf_load (struct ata_port*,struct ata_taskfile const*) ; 

__attribute__((used)) static void pdc_tf_load_mmio(struct ata_port *ap, const struct ata_taskfile *tf)
{
	WARN_ON(tf->protocol == ATA_PROT_DMA ||
		tf->protocol == ATAPI_PROT_DMA);
	ata_sff_tf_load(ap, tf);
}