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
struct ata_queued_cmd {int flags; } ;

/* Variables and functions */
 int ATA_QCFLAG_DMAMAP ; 
 int /*<<< orphan*/  sil_fill_sg (struct ata_queued_cmd*) ; 

__attribute__((used)) static void sil_qc_prep(struct ata_queued_cmd *qc)
{
	if (!(qc->flags & ATA_QCFLAG_DMAMAP))
		return;

	sil_fill_sg(qc);
}