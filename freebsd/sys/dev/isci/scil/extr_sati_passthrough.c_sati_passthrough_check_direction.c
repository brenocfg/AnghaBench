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
typedef  int /*<<< orphan*/  U8 ;
struct TYPE_3__ {scalar_t__ protocol; int /*<<< orphan*/  data_direction; } ;
typedef  TYPE_1__ SATI_TRANSLATOR_SEQUENCE_T ;
typedef  int /*<<< orphan*/  SATI_STATUS ;

/* Variables and functions */
 int PASSTHROUGH_CDB_T_DIR (int /*<<< orphan*/ *) ; 
 scalar_t__ PASSTHROUGH_PIO_DATA_IN ; 
 scalar_t__ PASSTHROUGH_PIO_DATA_OUT ; 
 scalar_t__ PASSTHROUGH_UDMA_DATA_IN ; 
 scalar_t__ PASSTHROUGH_UDMA_DATA_OUT ; 
 int /*<<< orphan*/  SATI_COMPLETE ; 
 int /*<<< orphan*/  SATI_DATA_DIRECTION_IN ; 
 int /*<<< orphan*/  SATI_DATA_DIRECTION_NONE ; 
 int /*<<< orphan*/  SATI_DATA_DIRECTION_OUT ; 
 int /*<<< orphan*/  SATI_FAILURE ; 

__attribute__((used)) static
SATI_STATUS sati_passthrough_check_direction(
   SATI_TRANSLATOR_SEQUENCE_T * sequence,
   U8           * cdb
)
{
   if ((sequence->protocol == PASSTHROUGH_PIO_DATA_IN) ||
       (sequence->protocol == PASSTHROUGH_UDMA_DATA_IN))
   {
      if (PASSTHROUGH_CDB_T_DIR(cdb) == 0x0)
      {
         return SATI_FAILURE;
      }
      else
      {
         sequence->data_direction = SATI_DATA_DIRECTION_IN;
      }
   }
   else if ((sequence->protocol == PASSTHROUGH_PIO_DATA_OUT) ||
            (sequence->protocol == PASSTHROUGH_UDMA_DATA_OUT))
   {
      if (PASSTHROUGH_CDB_T_DIR(cdb) == 0x1)
      {
         return SATI_FAILURE;
      }
      else
      {
         sequence->data_direction = SATI_DATA_DIRECTION_OUT;
      }
   }
   else
   {
      sequence->data_direction = SATI_DATA_DIRECTION_NONE;
   }

   return SATI_COMPLETE;
}