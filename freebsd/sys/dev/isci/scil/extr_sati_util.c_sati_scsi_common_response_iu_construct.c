#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  void* U8 ;
struct TYPE_3__ {void* data_present; void* status; void** sense_data_length; } ;
typedef  TYPE_1__ SCI_SSP_RESPONSE_IU_T ;

/* Variables and functions */

void sati_scsi_common_response_iu_construct(
   SCI_SSP_RESPONSE_IU_T * rsp_iu,
   U8                      scsi_status,
   U8                      sense_data_length,
   U8                      data_present
)
{
   rsp_iu->sense_data_length[3] = sense_data_length;
   rsp_iu->sense_data_length[2] = 0;
   rsp_iu->sense_data_length[1] = 0;
   rsp_iu->sense_data_length[0] = 0;
   rsp_iu->status               = scsi_status;
   rsp_iu->data_present         = data_present;
}