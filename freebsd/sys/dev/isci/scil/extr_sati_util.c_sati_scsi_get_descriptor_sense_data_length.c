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
 int SCSI_BLOCK_DESCRIPTOR_LENGTH ; 
 int SCSI_CMD_SPECIFIC_DESCRIPTOR_LENGTH ; 
 int SCSI_INFORMATION_DESCRIPTOR_LENGTH ; 
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
 int* sati_cb_get_cdb_address (void*) ; 
 int sati_get_cdb_byte (int*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static
U8 sati_scsi_get_descriptor_sense_data_length(SATI_TRANSLATOR_SEQUENCE_T * sequence,
        void * scsi_io)
{
    U8 * cdb = sati_cb_get_cdb_address(scsi_io);
    //Initial value is descriptor header length
    U8 length = 8;

    switch (sati_get_cdb_byte(cdb, 0))
    {
#if !defined(DISABLE_SATI_WRITE_LONG)
    case SCSI_WRITE_LONG_10:
    case SCSI_WRITE_LONG_16:
        length += SCSI_BLOCK_DESCRIPTOR_LENGTH +
            SCSI_INFORMATION_DESCRIPTOR_LENGTH;
        break;
#endif // !defined(DISABLE_SATI_WRITE_LONG)
#if !defined(DISABLE_SATI_REASSIGN_BLOCKS)
    case SCSI_REASSIGN_BLOCKS:
        length += SCSI_CMD_SPECIFIC_DESCRIPTOR_LENGTH +
            SCSI_INFORMATION_DESCRIPTOR_LENGTH;
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
        length += SCSI_INFORMATION_DESCRIPTOR_LENGTH;
        break;
    }

    return length;
}