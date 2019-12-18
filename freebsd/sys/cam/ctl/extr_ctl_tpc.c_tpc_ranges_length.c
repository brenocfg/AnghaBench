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
struct scsi_range_desc {int /*<<< orphan*/  length; } ;
typedef  int /*<<< orphan*/  off_t ;

/* Variables and functions */
 scalar_t__ scsi_4btoul (int /*<<< orphan*/ ) ; 

__attribute__((used)) static off_t
tpc_ranges_length(struct scsi_range_desc *range, int nrange)
{
	off_t length = 0;
	int r;

	for (r = 0; r < nrange; r++)
		length += scsi_4btoul(range[r].length);
	return (length);
}