#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct ata_queued_cmd {int nbytes; int curbytes; int sect_size; int /*<<< orphan*/  ap; TYPE_1__* dev; int /*<<< orphan*/  tf; } ;
struct TYPE_2__ {scalar_t__ multi_count; } ;

/* Variables and functions */
 int /*<<< orphan*/  WARN_ON_ONCE (int) ; 
 int /*<<< orphan*/  ata_pio_sector (struct ata_queued_cmd*) ; 
 int /*<<< orphan*/  ata_sff_sync (int /*<<< orphan*/ ) ; 
 scalar_t__ is_multi_taskfile (int /*<<< orphan*/ *) ; 
 unsigned int min (int,scalar_t__) ; 

__attribute__((used)) static void ata_pio_sectors(struct ata_queued_cmd *qc)
{
	if (is_multi_taskfile(&qc->tf)) {
		/* READ/WRITE MULTIPLE */
		unsigned int nsect;

		WARN_ON_ONCE(qc->dev->multi_count == 0);

		nsect = min((qc->nbytes - qc->curbytes) / qc->sect_size,
			    qc->dev->multi_count);
		while (nsect--)
			ata_pio_sector(qc);
	} else
		ata_pio_sector(qc);

	ata_sff_sync(qc->ap); /* flush */
}