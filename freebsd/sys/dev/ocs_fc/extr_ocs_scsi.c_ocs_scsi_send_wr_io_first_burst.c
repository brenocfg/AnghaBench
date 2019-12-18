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
typedef  int /*<<< orphan*/  ocs_scsi_sgl_t ;
typedef  int /*<<< orphan*/  ocs_scsi_rsp_io_cb_t ;
typedef  int /*<<< orphan*/  ocs_scsi_dif_info_t ;
typedef  int /*<<< orphan*/  ocs_node_t ;
typedef  int /*<<< orphan*/  ocs_io_t ;
typedef  int /*<<< orphan*/  int32_t ;

/* Variables and functions */
 int /*<<< orphan*/  OCS_HW_IO_INITIATOR_WRITE ; 
 int /*<<< orphan*/  ocs_scsi_send_io (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*) ; 

int32_t
ocs_scsi_send_wr_io_first_burst(ocs_node_t *node, ocs_io_t *io, uint64_t lun, void *cdb, uint32_t cdb_len,
	ocs_scsi_dif_info_t *dif_info,
	ocs_scsi_sgl_t *sgl, uint32_t sgl_count, uint32_t wire_len, uint32_t first_burst,
	ocs_scsi_rsp_io_cb_t cb, void *arg)
{
	int32_t rc;

	rc = ocs_scsi_send_io(OCS_HW_IO_INITIATOR_WRITE, node, io, lun, 0, cdb, cdb_len, dif_info, sgl, sgl_count,
			      wire_len, 0, cb, arg);

	return rc;
}