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
typedef  int /*<<< orphan*/  uint64_t ;
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int /*<<< orphan*/  ocs_scsi_vaddr_len_t ;
typedef  int /*<<< orphan*/  ocs_io_t ;
typedef  int int32_t ;

/* Variables and functions */

int32_t ocs_scsi_get_block_vaddr(ocs_io_t *io, uint64_t blocknumber,
				ocs_scsi_vaddr_len_t addrlen[],
				uint32_t max_addrlen, void **dif_vaddr)
{
	return -1;
}