#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int U8 ;
struct TYPE_6__ {int /*<<< orphan*/  is_sense_response_set; } ;
typedef  TYPE_1__ SATI_TRANSLATOR_SEQUENCE_T ;

/* Variables and functions */
#define  SCSI_DESCRIPTOR_CURRENT_RESPONSE_CODE 131 
#define  SCSI_DESCRIPTOR_DEFERRED_RESPONSE_CODE 130 
#define  SCSI_FIXED_CURRENT_RESPONSE_CODE 129 
#define  SCSI_FIXED_DEFERRED_RESPONSE_CODE 128 
 int /*<<< orphan*/  TRUE ; 
 int sati_scsi_get_sense_data_response_code (TYPE_1__*) ; 
 int /*<<< orphan*/  sati_scsi_read_error_descriptor_sense_construct (TYPE_1__*,void*,void*,int,int,int,int,int) ; 
 int /*<<< orphan*/  sati_scsi_read_error_fixed_sense_construct (TYPE_1__*,void*,void*,int,int,int,int,int) ; 

void sati_scsi_read_error_sense_construct(
   SATI_TRANSLATOR_SEQUENCE_T * sequence,
   void                       * scsi_io,
   void                       * ata_input_data,
   U8                           scsi_status,
   U8                           sense_key,
   U8                           additional_sense_code,
   U8                           additional_sense_code_qualifier
)
{
    U8 response_code;

    response_code = sati_scsi_get_sense_data_response_code(sequence);

    switch (response_code)
    {
    case SCSI_FIXED_CURRENT_RESPONSE_CODE:
    case SCSI_FIXED_DEFERRED_RESPONSE_CODE:
        sati_scsi_read_error_fixed_sense_construct(sequence, scsi_io, ata_input_data, scsi_status,
                response_code, sense_key, additional_sense_code, additional_sense_code_qualifier);
    break;
    case SCSI_DESCRIPTOR_CURRENT_RESPONSE_CODE:
    case SCSI_DESCRIPTOR_DEFERRED_RESPONSE_CODE:
        sati_scsi_read_error_descriptor_sense_construct(sequence, scsi_io, ata_input_data, scsi_status,
                response_code, sense_key, additional_sense_code, additional_sense_code_qualifier);
        break;
    }

    sequence->is_sense_response_set = TRUE;
}