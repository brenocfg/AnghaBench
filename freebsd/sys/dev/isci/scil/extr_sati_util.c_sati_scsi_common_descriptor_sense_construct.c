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
typedef  scalar_t__ U8 ;
typedef  int /*<<< orphan*/  U32 ;
typedef  int /*<<< orphan*/  SATI_TRANSLATOR_SEQUENCE_T ;

/* Variables and functions */
 int /*<<< orphan*/  sati_scsi_common_descriptors_construct (void*,scalar_t__*,int /*<<< orphan*/ ,scalar_t__*) ; 
 scalar_t__ sati_scsi_get_descriptor_sense_data_length (int /*<<< orphan*/ *,void*) ; 
 int /*<<< orphan*/  sati_set_sense_data_byte (scalar_t__*,int /*<<< orphan*/ ,int,scalar_t__) ; 

__attribute__((used)) static
void sati_scsi_common_descriptor_sense_construct(
    SATI_TRANSLATOR_SEQUENCE_T * sequence,
    void                       * scsi_io,
    U8                         * sense_data,
    U32                          sense_len,
    U8                           sense_key,
    U8                           additional_sense_code,
    U8                           additional_sense_code_qualifier,
    U8                         * information_buff
)
{
    sati_set_sense_data_byte(sense_data, sense_len, 1,  sense_key);
    sati_set_sense_data_byte(sense_data, sense_len, 2,  additional_sense_code);
    sati_set_sense_data_byte(sense_data, sense_len, 3,  additional_sense_code_qualifier);
    sati_set_sense_data_byte(sense_data, sense_len, 4,  0);
    sati_set_sense_data_byte(sense_data, sense_len, 5,  0);
    sati_set_sense_data_byte(sense_data, sense_len, 6,  0);

    sati_scsi_common_descriptors_construct(scsi_io, sense_data + 8, sense_len, information_buff);

    sati_set_sense_data_byte(sense_data, sense_len, 7,  sati_scsi_get_descriptor_sense_data_length(sequence, scsi_io) - 8);
}