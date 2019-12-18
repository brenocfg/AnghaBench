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
typedef  scalar_t__ U32 ;

/* Variables and functions */
 scalar_t__ SCSI_BLOCK_DESCRIPTOR_LENGTH ; 
 scalar_t__ SCSI_CMD_SPECIFIC_DESCRIPTOR_LENGTH ; 
 scalar_t__ SCSI_INFORMATION_DESCRIPTOR_LENGTH ; 
#define  SCSI_READ_10 144 
#define  SCSI_READ_12 143 
#define  SCSI_READ_16 142 
#define  SCSI_READ_6 141 
#define  SCSI_REASSIGN_BLOCKS 140 
#define  SCSI_VERIFY_10 139 
#define  SCSI_VERIFY_12 138 
#define  SCSI_VERIFY_16 137 
#define  SCSI_WRITE_10 136 
#define  SCSI_WRITE_12 135 
#define  SCSI_WRITE_16 134 
#define  SCSI_WRITE_6 133 
#define  SCSI_WRITE_AND_VERIFY_10 132 
#define  SCSI_WRITE_AND_VERIFY_12 131 
#define  SCSI_WRITE_AND_VERIFY_16 130 
#define  SCSI_WRITE_LONG_10 129 
#define  SCSI_WRITE_LONG_16 128 
 scalar_t__* sati_cb_get_cdb_address (void*) ; 
 int sati_get_cdb_byte (scalar_t__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sati_scsi_block_descriptor_construct (scalar_t__*,scalar_t__) ; 
 int /*<<< orphan*/  sati_scsi_command_specific_descriptor_construct (scalar_t__*,scalar_t__,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sati_scsi_information_descriptor_construct (scalar_t__*,scalar_t__,scalar_t__*) ; 

__attribute__((used)) static
void sati_scsi_common_descriptors_construct(
    void    * scsi_io,
    U8      * sense_data,
    U32       sense_len,
    U8      * information_buff)
{
    U8 * cdb = sati_cb_get_cdb_address(scsi_io);
    U8 offset = 0;

    switch (sati_get_cdb_byte(cdb, 0))
    {
#if !defined(DISABLE_SATI_WRITE_LONG)
    case SCSI_WRITE_LONG_10:
    case SCSI_WRITE_LONG_16:
        sati_scsi_block_descriptor_construct(
                sense_data + offset,
                sense_len - offset);

        offset += SCSI_BLOCK_DESCRIPTOR_LENGTH;
        sati_scsi_information_descriptor_construct(
                  sense_data + offset,
                  sense_len - offset,
                  information_buff);

        offset += SCSI_INFORMATION_DESCRIPTOR_LENGTH;
        break;
#endif // !defined(DISABLE_SATI_WRITE_LONG)
#if !defined(DISABLE_SATI_REASSIGN_BLOCKS)
    case SCSI_REASSIGN_BLOCKS:
        sati_scsi_command_specific_descriptor_construct(
          sense_data + offset,
          sense_len - offset,
          NULL);

        offset += SCSI_CMD_SPECIFIC_DESCRIPTOR_LENGTH;
        sati_scsi_information_descriptor_construct(
                  sense_data + offset,
                  sense_len - offset,
                  information_buff);

        offset += SCSI_INFORMATION_DESCRIPTOR_LENGTH;
        break;
#endif // !defined(DISABLE_SATI_REASSIGN_BLOCKS)
    case SCSI_READ_6:
    case SCSI_READ_10:
    case SCSI_READ_12:
    case SCSI_READ_16:
    case SCSI_WRITE_6:
    case SCSI_WRITE_10:
    case SCSI_WRITE_12:
    case SCSI_WRITE_16:
#if !defined(DISABLE_SATI_VERIFY)
    case SCSI_VERIFY_10:
    case SCSI_VERIFY_12:
    case SCSI_VERIFY_16:
#endif // !defined(DISABLE_SATI_VERIFY)
#if    !defined(DISABLE_SATI_WRITE_AND_VERIFY)  \
    && !defined(DISABLE_SATI_VERIFY)            \
    && !defined(DISABLE_SATI_WRITE)

    case SCSI_WRITE_AND_VERIFY_10:
    case SCSI_WRITE_AND_VERIFY_12:
    case SCSI_WRITE_AND_VERIFY_16:
#endif //    !defined(DISABLE_SATI_WRITE_AND_VERIFY)
       // && !defined(DISABLE_SATI_VERIFY)
       // && !defined(DISABLE_SATI_WRITE)
        sati_scsi_information_descriptor_construct(
                  sense_data + offset,
                  sense_len - offset,
                  information_buff);

        offset += SCSI_INFORMATION_DESCRIPTOR_LENGTH;
        break;
    }
}