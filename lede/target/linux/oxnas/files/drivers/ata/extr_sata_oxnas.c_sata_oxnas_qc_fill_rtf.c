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
struct ata_queued_cmd {int /*<<< orphan*/  result_tf; int /*<<< orphan*/  ap; } ;

/* Variables and functions */
 int /*<<< orphan*/  sata_oxnas_tf_read (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static bool sata_oxnas_qc_fill_rtf(struct ata_queued_cmd *qc)
{
	/* Read the most recently received FIS from the SATA core ORB registers
	 and convert to an ATA taskfile */
	sata_oxnas_tf_read(qc->ap, &qc->result_tf);
	return true;
}