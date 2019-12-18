#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  U8 ;
struct TYPE_6__ {int /*<<< orphan*/  type; TYPE_1__* device; } ;
struct TYPE_5__ {int capabilities; } ;
typedef  TYPE_2__ SATI_TRANSLATOR_SEQUENCE_T ;
typedef  int /*<<< orphan*/  SATI_STATUS ;

/* Variables and functions */
 int SATI_DEVICE_CAP_SMART_SUPPORT ; 
 int /*<<< orphan*/  SATI_FAILURE_CHECK_RESPONSE_DATA ; 
 int /*<<< orphan*/  SATI_SEQUENCE_MODE_SENSE_10_ALL_PAGES ; 
 int /*<<< orphan*/  SATI_SEQUENCE_MODE_SENSE_10_CACHING ; 
 int /*<<< orphan*/  SATI_SEQUENCE_MODE_SENSE_10_CONTROL ; 
 int /*<<< orphan*/  SATI_SEQUENCE_MODE_SENSE_10_DISCONNECT_RECONNECT ; 
 int /*<<< orphan*/  SATI_SEQUENCE_MODE_SENSE_10_INFORMATIONAL_EXCP_CONTROL ; 
 int /*<<< orphan*/  SATI_SEQUENCE_MODE_SENSE_10_POWER_CONDITION ; 
 int /*<<< orphan*/  SATI_SEQUENCE_MODE_SENSE_10_READ_WRITE_ERROR ; 
 int /*<<< orphan*/  SATI_SEQUENCE_MODE_SENSE_6_ALL_PAGES ; 
 int /*<<< orphan*/  SATI_SEQUENCE_MODE_SENSE_6_CACHING ; 
 int /*<<< orphan*/  SATI_SEQUENCE_MODE_SENSE_6_CONTROL ; 
 int /*<<< orphan*/  SATI_SEQUENCE_MODE_SENSE_6_DISCONNECT_RECONNECT ; 
 int /*<<< orphan*/  SATI_SEQUENCE_MODE_SENSE_6_INFORMATIONAL_EXCP_CONTROL ; 
 int /*<<< orphan*/  SATI_SEQUENCE_MODE_SENSE_6_POWER_CONDITION ; 
 int /*<<< orphan*/  SATI_SEQUENCE_MODE_SENSE_6_READ_WRITE_ERROR ; 
 int /*<<< orphan*/  SATI_SUCCESS ; 
 int /*<<< orphan*/  SCSI_ASCQ_INVALID_FIELD_IN_CDB ; 
 int /*<<< orphan*/  SCSI_ASCQ_INVALID_FIELD_IN_PARM_LIST ; 
 int /*<<< orphan*/  SCSI_ASC_INVALID_FIELD_IN_CDB ; 
 int /*<<< orphan*/  SCSI_ASC_INVALID_FIELD_IN_PARM_LIST ; 
#define  SCSI_MODE_PAGE_ALL_PAGES 134 
#define  SCSI_MODE_PAGE_CACHING 133 
#define  SCSI_MODE_PAGE_CONTROL 132 
#define  SCSI_MODE_PAGE_DISCONNECT_RECONNECT 131 
#define  SCSI_MODE_PAGE_INFORMATIONAL_EXCP_CONTROL 130 
#define  SCSI_MODE_PAGE_POWER_CONDITION 129 
#define  SCSI_MODE_PAGE_READ_WRITE_ERROR 128 
 int SCSI_MODE_SENSE_6 ; 
 int SCSI_MODE_SENSE_PAGE_CODE_ENABLE ; 
 int /*<<< orphan*/  SCSI_SENSE_ILLEGAL_REQUEST ; 
 int /*<<< orphan*/  SCSI_STATUS_CHECK_CONDITION ; 
 int /*<<< orphan*/ * sati_cb_get_cdb_address (void*) ; 
 int sati_get_cdb_byte (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  sati_scsi_sense_data_construct (TYPE_2__*,void*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static
SATI_STATUS sati_mode_sense_is_page_code_supported(
   SATI_TRANSLATOR_SEQUENCE_T * sequence,
   void                       * scsi_io,
   U8                           cdb_length
)
{
   U8 * cdb = sati_cb_get_cdb_address(scsi_io);

   switch (sati_get_cdb_byte(cdb, 2) & SCSI_MODE_SENSE_PAGE_CODE_ENABLE)
   {
      case SCSI_MODE_PAGE_CACHING:
         if (sati_get_cdb_byte(cdb, 0) == SCSI_MODE_SENSE_6)
            sequence->type = SATI_SEQUENCE_MODE_SENSE_6_CACHING;
         else
            sequence->type = SATI_SEQUENCE_MODE_SENSE_10_CACHING;
      break;

      case SCSI_MODE_PAGE_ALL_PAGES:
         if (sati_get_cdb_byte(cdb, 0) == SCSI_MODE_SENSE_6)
            sequence->type = SATI_SEQUENCE_MODE_SENSE_6_ALL_PAGES;
         else
            sequence->type = SATI_SEQUENCE_MODE_SENSE_10_ALL_PAGES;
      break;

      case SCSI_MODE_PAGE_READ_WRITE_ERROR:
         if (sati_get_cdb_byte(cdb, 0) == SCSI_MODE_SENSE_6)
            sequence->type = SATI_SEQUENCE_MODE_SENSE_6_READ_WRITE_ERROR;
         else
            sequence->type = SATI_SEQUENCE_MODE_SENSE_10_READ_WRITE_ERROR;
      break;

      case SCSI_MODE_PAGE_DISCONNECT_RECONNECT:
         if (sati_get_cdb_byte(cdb, 0) == SCSI_MODE_SENSE_6)
            sequence->type = SATI_SEQUENCE_MODE_SENSE_6_DISCONNECT_RECONNECT;
         else
            sequence->type = SATI_SEQUENCE_MODE_SENSE_10_DISCONNECT_RECONNECT;
      break;

      case SCSI_MODE_PAGE_CONTROL:
         if (sati_get_cdb_byte(cdb, 0) == SCSI_MODE_SENSE_6)
            sequence->type = SATI_SEQUENCE_MODE_SENSE_6_CONTROL;
         else
            sequence->type = SATI_SEQUENCE_MODE_SENSE_10_CONTROL;
      break;

      case SCSI_MODE_PAGE_POWER_CONDITION:
         if (sati_get_cdb_byte(cdb, 0) == SCSI_MODE_SENSE_6)
            sequence->type = SATI_SEQUENCE_MODE_SENSE_6_POWER_CONDITION;
         else
            sequence->type = SATI_SEQUENCE_MODE_SENSE_10_POWER_CONDITION;
      break;

      case SCSI_MODE_PAGE_INFORMATIONAL_EXCP_CONTROL:
         // The informational exceptions control page is only useful
         // if SMART is supported.
         if ((sequence->device->capabilities | SATI_DEVICE_CAP_SMART_SUPPORT)
             == 0)
         {
            // For a MODE SENSE, utilize INVALID FIELD IN CDB,
            // For a MODE SELECT, utilize INVALID FIELD IN PARAMETER LIST.
            if (sati_get_cdb_byte(cdb, 0) == SCSI_MODE_SENSE_6)
            {
               sati_scsi_sense_data_construct(
                  sequence,
                  scsi_io,
                  SCSI_STATUS_CHECK_CONDITION,
                  SCSI_SENSE_ILLEGAL_REQUEST,
                  SCSI_ASC_INVALID_FIELD_IN_CDB,
                  SCSI_ASCQ_INVALID_FIELD_IN_CDB
               );
            }
            else
            {
               sati_scsi_sense_data_construct(
                  sequence,
                  scsi_io,
                  SCSI_STATUS_CHECK_CONDITION,
                  SCSI_SENSE_ILLEGAL_REQUEST,
                  SCSI_ASC_INVALID_FIELD_IN_PARM_LIST,
                  SCSI_ASCQ_INVALID_FIELD_IN_PARM_LIST
               );
            }

            return SATI_FAILURE_CHECK_RESPONSE_DATA;
         }

         if (sati_get_cdb_byte(cdb, 0) == SCSI_MODE_SENSE_6)
            sequence->type = SATI_SEQUENCE_MODE_SENSE_6_INFORMATIONAL_EXCP_CONTROL;
         else
            sequence->type = SATI_SEQUENCE_MODE_SENSE_10_INFORMATIONAL_EXCP_CONTROL;
      break;

      default:
         sati_scsi_sense_data_construct(
            sequence,
            scsi_io,
            SCSI_STATUS_CHECK_CONDITION,
            SCSI_SENSE_ILLEGAL_REQUEST,
            SCSI_ASC_INVALID_FIELD_IN_CDB,
            SCSI_ASCQ_INVALID_FIELD_IN_CDB
         );
         return SATI_FAILURE_CHECK_RESPONSE_DATA;
      break;
   }

   return SATI_SUCCESS;
}