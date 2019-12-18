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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  uint64_t ;
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int /*<<< orphan*/  ocs_io_t ;
typedef  int /*<<< orphan*/  ocs_dma_t ;
typedef  int int32_t ;

/* Variables and functions */

int32_t ocs_scsi_recv_cmd_first_burst(ocs_io_t *io, uint64_t lun, uint8_t *cdb,
		 			uint32_t cdb_len, uint32_t flags, 
					ocs_dma_t first_burst_buffers[], 
					uint32_t first_burst_buffer_count)
{
	return -1;
}