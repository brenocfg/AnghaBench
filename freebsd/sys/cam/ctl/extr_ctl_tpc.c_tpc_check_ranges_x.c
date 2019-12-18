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
typedef  scalar_t__ uint64_t ;
typedef  scalar_t__ uint32_t ;
struct scsi_range_desc {int /*<<< orphan*/  length; int /*<<< orphan*/  lba; } ;

/* Variables and functions */
 scalar_t__ scsi_4btoul (int /*<<< orphan*/ ) ; 
 scalar_t__ scsi_8btou64 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
tpc_check_ranges_x(struct scsi_range_desc *range, int nrange)
{
	uint64_t b1, b2;
	uint32_t l1, l2;
	int i, j;

	for (i = 0; i < nrange - 1; i++) {
		b1 = scsi_8btou64(range[i].lba);
		l1 = scsi_4btoul(range[i].length);
		for (j = i + 1; j < nrange; j++) {
			b2 = scsi_8btou64(range[j].lba);
			l2 = scsi_4btoul(range[j].length);
			if (b1 + l1 > b2 && b2 + l2 > b1)
				return (-1);
		}
	}
	return (0);
}