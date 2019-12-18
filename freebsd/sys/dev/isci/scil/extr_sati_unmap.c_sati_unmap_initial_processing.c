#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  int U8 ;
typedef  size_t U32 ;
typedef  size_t U16 ;
struct TYPE_12__ {size_t max_unmap_block_descriptors; size_t max_lba_range_entries; size_t current_unmap_block_descriptor_index; int /*<<< orphan*/  unmap_buffer_sgl_pair; int /*<<< orphan*/ * virtual_unmap_buffer; int /*<<< orphan*/  physical_unmap_buffer_high; int /*<<< orphan*/  physical_unmap_buffer_low; } ;
struct TYPE_10__ {TYPE_3__ unmap_process_state; } ;
struct TYPE_13__ {size_t allocation_length; int /*<<< orphan*/  state; TYPE_2__* device; int /*<<< orphan*/  type; TYPE_1__ command_specific_data; } ;
struct TYPE_11__ {int capabilities; size_t logical_block_size; } ;
typedef  int /*<<< orphan*/  TRIM_PAIR ;
typedef  TYPE_3__ SATI_UNMAP_PROCESSING_STATE_T ;
typedef  TYPE_4__ SATI_TRANSLATOR_SEQUENCE_T ;
typedef  int /*<<< orphan*/  SATI_STATUS ;

/* Variables and functions */
 int /*<<< orphan*/  SATI_COMPLETE ; 
 int SATI_DEVICE_CAP_DSM_TRIM_SUPPORT ; 
 int /*<<< orphan*/  SATI_FAILURE_CHECK_RESPONSE_DATA ; 
 int /*<<< orphan*/  SATI_SEQUENCE_STATE_INCOMPLETE ; 
 int /*<<< orphan*/  SATI_SEQUENCE_UNMAP ; 
 int /*<<< orphan*/  SATI_SUCCESS ; 
 size_t SATI_UNMAP_SIZEOF_SCSI_UNMAP_BLOCK_DESCRIPTOR ; 
 size_t SATI_UNMAP_SIZEOF_SCSI_UNMAP_PARAMETER_LIST ; 
 int /*<<< orphan*/  SCSI_ASCQ_INVALID_FIELD_IN_CDB ; 
 int /*<<< orphan*/  SCSI_ASCQ_NO_ADDITIONAL_SENSE ; 
 int /*<<< orphan*/  SCSI_ASC_INVALID_FIELD_IN_CDB ; 
 int /*<<< orphan*/  SCSI_ASC_NO_ADDITIONAL_SENSE ; 
 int /*<<< orphan*/  SCSI_SENSE_ILLEGAL_REQUEST ; 
 int /*<<< orphan*/  SCSI_SENSE_NO_SENSE ; 
 int /*<<< orphan*/  SCSI_STATUS_BUSY ; 
 int /*<<< orphan*/  SCSI_STATUS_CHECK_CONDITION ; 
 int /*<<< orphan*/  sati_cb_allocate_dma_buffer (void*,size_t,int /*<<< orphan*/ **,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int* sati_cb_get_cdb_address (void*) ; 
 int /*<<< orphan*/  sati_cb_sgl_next_sge (void*,void*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int sati_get_cdb_byte (int*,int) ; 
 int /*<<< orphan*/  sati_get_data_byte (TYPE_4__*,void*,size_t,int*) ; 
 int /*<<< orphan*/  sati_scsi_sense_data_construct (TYPE_4__*,void*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 size_t sati_unmap_get_max_buffer_size_in_blocks (TYPE_4__*) ; 
 int /*<<< orphan*/  sati_unmap_load_next_descriptor (TYPE_4__*,void*) ; 

SATI_STATUS sati_unmap_initial_processing(
   SATI_TRANSLATOR_SEQUENCE_T * sequence,
   void                       * scsi_io,
   void                       * ata_io
)
{
   SATI_UNMAP_PROCESSING_STATE_T * unmap_process_state;
   U8 * cdb;
   U16 unmap_length;
   U32 descriptor_length;
   U32 index;
   U32 max_dsm_blocks;
   U8  unmap_param_list[8];

   unmap_process_state = &sequence->command_specific_data.unmap_process_state;

   // Set up the sequence type for unmap translation
   sequence->type = SATI_SEQUENCE_UNMAP;

   // Make sure the device is TRIM capable
   if ((sequence->device->capabilities & SATI_DEVICE_CAP_DSM_TRIM_SUPPORT)
       != SATI_DEVICE_CAP_DSM_TRIM_SUPPORT)
   {
      // Can't send TRIM request to device that does not support it
      sati_scsi_sense_data_construct(
         sequence,
         scsi_io,
         SCSI_STATUS_CHECK_CONDITION,
         SCSI_SENSE_ILLEGAL_REQUEST,
         SCSI_ASC_INVALID_FIELD_IN_CDB,
         SCSI_ASCQ_INVALID_FIELD_IN_CDB
      );
      return SATI_FAILURE_CHECK_RESPONSE_DATA;
   }

   // get the amount of data being sent from the cdb
   cdb = sati_cb_get_cdb_address(scsi_io);
   unmap_length = (sati_get_cdb_byte(cdb, 7) << 8) | sati_get_cdb_byte(cdb, 8);

   // If nothing has been requested return success now.
   if (unmap_length == 0)
   {
       // SAT: This is not an error
       return SATI_SUCCESS;
   }
   if (unmap_length < SATI_UNMAP_SIZEOF_SCSI_UNMAP_PARAMETER_LIST)
   {
      // Not enough length specified in the CDB
      sati_scsi_sense_data_construct(
         sequence,
         scsi_io,
         SCSI_STATUS_CHECK_CONDITION,
         SCSI_SENSE_ILLEGAL_REQUEST,
         SCSI_ASC_INVALID_FIELD_IN_CDB,
         SCSI_ASCQ_INVALID_FIELD_IN_CDB
      );
      return SATI_FAILURE_CHECK_RESPONSE_DATA;
   }

   sequence->allocation_length = unmap_length;

   // Get the unmap parameter header
   for(index = 0; index < SATI_UNMAP_SIZEOF_SCSI_UNMAP_PARAMETER_LIST; index++)
   {
      sati_get_data_byte(sequence, scsi_io, index,   &unmap_param_list[index]);
   }
   descriptor_length = (unmap_param_list[2] << 8) | unmap_param_list[3];

   // Check length again
   if (descriptor_length == 0)
   {
       // SAT: This is not an error
       return SATI_SUCCESS;
   }

   if ((U32)(unmap_length - SATI_UNMAP_SIZEOF_SCSI_UNMAP_PARAMETER_LIST) < descriptor_length)
   {
      // Not enough length specified in the CDB
      sati_scsi_sense_data_construct(
         sequence,
         scsi_io,
         SCSI_STATUS_CHECK_CONDITION,
         SCSI_SENSE_ILLEGAL_REQUEST,
         SCSI_ASC_INVALID_FIELD_IN_CDB,
         SCSI_ASCQ_INVALID_FIELD_IN_CDB
      );
      return SATI_FAILURE_CHECK_RESPONSE_DATA;
   }

   // Save the maximum unmap block descriptors in this request
   unmap_process_state->max_unmap_block_descriptors =
       descriptor_length/SATI_UNMAP_SIZEOF_SCSI_UNMAP_BLOCK_DESCRIPTOR;

   // Determine the maximum size of the write buffer that will be required
   // for the translation in terms of number of blocks
   max_dsm_blocks = sati_unmap_get_max_buffer_size_in_blocks(sequence);

   // Save the maximum number of DSM descriptors we can send during the translation
   unmap_process_state->max_lba_range_entries =
       (max_dsm_blocks*sequence->device->logical_block_size)/sizeof(TRIM_PAIR);

   // Get the write buffer for the translation
   sati_cb_allocate_dma_buffer(
      scsi_io,
      max_dsm_blocks*sequence->device->logical_block_size,
      &(unmap_process_state->virtual_unmap_buffer),
      &(unmap_process_state->physical_unmap_buffer_low),
      &(unmap_process_state->physical_unmap_buffer_high));

   // Makes sure we have a buffer
   if (unmap_process_state->virtual_unmap_buffer == NULL)
   {
      // Resource failure
      sati_scsi_sense_data_construct(
         sequence,
         scsi_io,
         SCSI_STATUS_BUSY,
         SCSI_SENSE_NO_SENSE,
         SCSI_ASC_NO_ADDITIONAL_SENSE,
         SCSI_ASCQ_NO_ADDITIONAL_SENSE
      );
      return SATI_FAILURE_CHECK_RESPONSE_DATA;
   }

   // Get the first SGL entry.  This code will only use one 4K page so will
   // only utilize the first sge.
   sati_cb_sgl_next_sge(scsi_io,
                        ata_io,
                        NULL,
                        &(unmap_process_state->unmap_buffer_sgl_pair));

   // Load the first descriptor to start the translation loop
   unmap_process_state->current_unmap_block_descriptor_index =
      SATI_UNMAP_SIZEOF_SCSI_UNMAP_PARAMETER_LIST;
   sati_unmap_load_next_descriptor(sequence,scsi_io);

   // Next state will be incomplete since translation
   // will require a callback and possibly more requests.
   sequence->state = SATI_SEQUENCE_STATE_INCOMPLETE;

   return SATI_COMPLETE;
}