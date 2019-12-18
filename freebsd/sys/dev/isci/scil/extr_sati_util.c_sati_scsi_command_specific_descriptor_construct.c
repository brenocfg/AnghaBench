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
typedef  int /*<<< orphan*/  U32 ;

/* Variables and functions */
 int SCSI_CMD_SPECIFIC_DESCRIPTOR_ADDITIONAL_LENGTH ; 
 int SCSI_CMD_SPECIFIC_DESCRIPTOR_TYPE ; 
 int /*<<< orphan*/  sati_set_sense_data_byte (int*,int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static
void sati_scsi_command_specific_descriptor_construct(
    U8       * sense_data,
    U32        sense_len,
    U8       * information_buff)
{
    U8 i;

    sati_set_sense_data_byte(sense_data, sense_len, 0,  SCSI_CMD_SPECIFIC_DESCRIPTOR_TYPE);
    sati_set_sense_data_byte(sense_data, sense_len, 1,  SCSI_CMD_SPECIFIC_DESCRIPTOR_ADDITIONAL_LENGTH);
    sati_set_sense_data_byte(sense_data, sense_len, 2,  0);
    sati_set_sense_data_byte(sense_data, sense_len, 3,  0);

    // fill information buffer
    // SBC 5.20.1 REASSIGN BLOCKS command overview
    // If information about the first LBA not reassigned is not available
    // COMMAND-SPECIFIC INFORMATION field shall be set to FFFF_FFFF_FFFF_FFFFh
    for (i=0; i<8; i++)
        sati_set_sense_data_byte(sense_data, sense_len, 4 + i, information_buff==NULL?0xFF:information_buff[i]);
}