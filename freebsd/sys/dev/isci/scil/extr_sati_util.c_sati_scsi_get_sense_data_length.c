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
typedef  int U8 ;
typedef  int /*<<< orphan*/  SATI_TRANSLATOR_SEQUENCE_T ;

/* Variables and functions */
#define  SCSI_DESCRIPTOR_CURRENT_RESPONSE_CODE 131 
#define  SCSI_DESCRIPTOR_DEFERRED_RESPONSE_CODE 130 
#define  SCSI_FIXED_CURRENT_RESPONSE_CODE 129 
#define  SCSI_FIXED_DEFERRED_RESPONSE_CODE 128 
 int SCSI_FIXED_SENSE_DATA_BASE_LENGTH ; 
 int sati_scsi_get_descriptor_sense_data_length (int /*<<< orphan*/ *,void*) ; 
 int sati_scsi_get_sense_data_response_code (int /*<<< orphan*/ *) ; 

U8 sati_scsi_get_sense_data_length(SATI_TRANSLATOR_SEQUENCE_T * sequence, void * scsi_io)
{
    U8 response_code;

    response_code = sati_scsi_get_sense_data_response_code(sequence);

    switch (response_code)
    {
    case SCSI_FIXED_CURRENT_RESPONSE_CODE:
    case SCSI_FIXED_DEFERRED_RESPONSE_CODE:
        return SCSI_FIXED_SENSE_DATA_BASE_LENGTH;
    break;
    case SCSI_DESCRIPTOR_CURRENT_RESPONSE_CODE:
    case SCSI_DESCRIPTOR_DEFERRED_RESPONSE_CODE:
        return sati_scsi_get_descriptor_sense_data_length(sequence, scsi_io);
    break;
    }

    return SCSI_FIXED_SENSE_DATA_BASE_LENGTH;
}