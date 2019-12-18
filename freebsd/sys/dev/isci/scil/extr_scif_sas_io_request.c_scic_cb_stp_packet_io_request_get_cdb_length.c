#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  U32 ;
struct TYPE_10__ {scalar_t__ state; } ;
struct TYPE_7__ {int /*<<< orphan*/  associated_object; } ;
struct TYPE_8__ {TYPE_2__ parent; } ;
struct TYPE_6__ {TYPE_5__ sequence; } ;
struct TYPE_9__ {TYPE_3__ parent; TYPE_1__ stp; } ;
typedef  TYPE_4__ SCIF_SAS_REQUEST_T ;
typedef  TYPE_5__ SATI_TRANSLATOR_SEQUENCE_T ;

/* Variables and functions */
 int /*<<< orphan*/  SATI_ATAPI_REQUEST_SENSE_CDB_LENGTH ; 
 scalar_t__ SATI_SEQUENCE_STATE_INCOMPLETE ; 
 int /*<<< orphan*/  scif_cb_io_request_get_cdb_length (int /*<<< orphan*/ ) ; 

U32 scic_cb_stp_packet_io_request_get_cdb_length(
   void * scic_user_io_request
)
{
   SCIF_SAS_REQUEST_T * fw_request = (SCIF_SAS_REQUEST_T*)
                                   scic_user_io_request;

   SATI_TRANSLATOR_SEQUENCE_T * sati_sequence = &fw_request->stp.sequence;

   if (sati_sequence->state != SATI_SEQUENCE_STATE_INCOMPLETE)
      return scif_cb_io_request_get_cdb_length(
                fw_request->parent.parent.associated_object
             );
   else
      return SATI_ATAPI_REQUEST_SENSE_CDB_LENGTH;
}