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
typedef  scalar_t__ U32 ;
struct TYPE_3__ {int /*<<< orphan*/  current_mode_page_processed; int /*<<< orphan*/  mode_page_offset; int /*<<< orphan*/  size_of_data_processed; } ;
typedef  int /*<<< orphan*/  SATI_STATUS ;
typedef  TYPE_1__ SATI_MODE_SELECT_PROCESSING_STATE_T ;

/* Variables and functions */
 int /*<<< orphan*/  SATI_COMPLETE ; 
 int /*<<< orphan*/  SATI_FAILURE_CHECK_RESPONSE_DATA ; 
 int /*<<< orphan*/  TRUE ; 

__attribute__((used)) static
SATI_STATUS sati_mode_select_process_mode_page_disconnect_reconnect(
   SATI_MODE_SELECT_PROCESSING_STATE_T * mode_select_process_state,
   U32 page_size
   )
{
   SATI_STATUS status = SATI_FAILURE_CHECK_RESPONSE_DATA;

   // No need to check data for valid or invalid this page (undefined)
   // No ata command to send
   {
      mode_select_process_state->size_of_data_processed += page_size;
      mode_select_process_state->mode_page_offset += page_size;
      mode_select_process_state->current_mode_page_processed = TRUE;
   }

   // No further interaction with remote devices
   status = SATI_COMPLETE;

   return status;
}