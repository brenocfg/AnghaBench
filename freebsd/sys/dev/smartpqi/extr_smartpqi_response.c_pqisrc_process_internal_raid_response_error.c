#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int uint16_t ;
struct TYPE_9__ {char* error_info; int req_pending; void* status; } ;
typedef  TYPE_2__ rcb_t ;
struct TYPE_10__ {scalar_t__ status; scalar_t__ data_in_result; scalar_t__ data_out_result; } ;
typedef  TYPE_3__ raid_path_error_info_elem_t ;
struct TYPE_8__ {scalar_t__ virt_addr; } ;
struct TYPE_11__ {TYPE_1__ err_buf_dma_mem; } ;
typedef  TYPE_4__ pqisrc_softstate_t ;
typedef  int /*<<< orphan*/  error_info ;

/* Variables and functions */
 int /*<<< orphan*/  DBG_FUNC (char*) ; 
 int /*<<< orphan*/  DBG_INFO (char*,scalar_t__,scalar_t__,scalar_t__) ; 
 int PQI_ERROR_BUFFER_ELEMENT_LENGTH ; 
 scalar_t__ PQI_RAID_DATA_IN_OUT_GOOD ; 
 void* REQUEST_FAILED ; 
 void* REQUEST_SUCCESS ; 
 int /*<<< orphan*/  memcpy (TYPE_3__*,char*,int) ; 

void  pqisrc_process_internal_raid_response_error(pqisrc_softstate_t *softs,
				       rcb_t *rcb, uint16_t err_idx)
{
	raid_path_error_info_elem_t error_info;

	DBG_FUNC("IN");

	rcb->error_info = (char *) (softs->err_buf_dma_mem.virt_addr) +
			  (err_idx * PQI_ERROR_BUFFER_ELEMENT_LENGTH);
	rcb->status = REQUEST_SUCCESS;
	memcpy(&error_info, rcb->error_info, sizeof(error_info));

	DBG_INFO("error_status 0x%x data_in_result 0x%x data_out_result 0x%x\n",
		error_info.status, error_info.data_in_result, error_info.data_out_result);

	if (error_info.status != 0)
		rcb->status = REQUEST_FAILED;
	if (error_info.data_in_result != PQI_RAID_DATA_IN_OUT_GOOD)
		rcb->status = REQUEST_FAILED;
	if (error_info.data_out_result != PQI_RAID_DATA_IN_OUT_GOOD)
		rcb->status = REQUEST_FAILED;

	rcb->req_pending = false;

	DBG_FUNC("OUT");
}