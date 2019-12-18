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
typedef  int /*<<< orphan*/  U8 ;
typedef  int /*<<< orphan*/  U32 ;
struct TYPE_2__ {int data_present; int* response_data_length; scalar_t__ data; scalar_t__ status; } ;
typedef  TYPE_1__ SCI_SSP_RESPONSE_IU_T ;
typedef  int /*<<< orphan*/  SATI_TRANSLATOR_SEQUENCE_T ;

/* Variables and functions */
 scalar_t__ sati_cb_get_response_iu_address (void*) ; 

void sati_scsi_response_data_construct(
   SATI_TRANSLATOR_SEQUENCE_T * sequence,
   void                       * scsi_io,
   U8                           response_data
)
{
#ifdef SATI_TRANSPORT_SUPPORTS_SAS
   SCI_SSP_RESPONSE_IU_T * rsp_iu  = (SCI_SSP_RESPONSE_IU_T*)
                                        sati_cb_get_response_iu_address(scsi_io);
   rsp_iu->data_present            = 0x01;
   rsp_iu->response_data_length[3] = sizeof(U32);
   rsp_iu->status                  = 0;
   ((U8 *)rsp_iu->data)[3]         = response_data;
#else
#endif // SATI_TRANSPORT_SUPPORTS_SAS
}