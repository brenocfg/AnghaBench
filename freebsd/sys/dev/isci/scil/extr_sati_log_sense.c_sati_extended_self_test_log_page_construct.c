#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {scalar_t__* self_test_descriptor_index; } ;
typedef  int /*<<< orphan*/  SATI_TRANSLATOR_SEQUENCE_T ;
typedef  TYPE_1__ ATA_EXTENDED_SMART_SELF_TEST_LOG_T ;

/* Variables and functions */
 int /*<<< orphan*/  sati_get_self_test_results (int /*<<< orphan*/ *,void*,TYPE_1__*) ; 
 int /*<<< orphan*/  sati_self_test_log_header_construct (int /*<<< orphan*/ *,void*) ; 
 int /*<<< orphan*/  sati_set_parameters_to_zero (int /*<<< orphan*/ *,void*) ; 

__attribute__((used)) static
void sati_extended_self_test_log_page_construct(
   SATI_TRANSLATOR_SEQUENCE_T  * sequence,
   void                        * scsi_io,
   void                        * ata_data
)
{
   ATA_EXTENDED_SMART_SELF_TEST_LOG_T * ata_log =
                  (ATA_EXTENDED_SMART_SELF_TEST_LOG_T*) ata_data;

   sati_self_test_log_header_construct(sequence, scsi_io);

   //bytes 4-19
   if( (ata_log->self_test_descriptor_index[0] == 0) &&
       (ata_log->self_test_descriptor_index[1] == 0))
   {
      sati_set_parameters_to_zero(sequence, scsi_io);
   }
   else
   {
      sati_get_self_test_results(sequence, scsi_io, ata_log);
   }
}