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
typedef  int /*<<< orphan*/  U32 ;
typedef  int /*<<< orphan*/  SATA_FIS_REG_D2H_T ;

/* Variables and functions */
 int /*<<< orphan*/  memcpy (char*,void*,int) ; 

void scic_sds_controller_copy_sata_response(
   void * response_buffer,
   void * frame_header,
   void * frame_buffer
)
{
   memcpy(
      response_buffer,
      frame_header,
      sizeof(U32)
   );

   memcpy(
      (char *)((char *)response_buffer + sizeof(U32)),
      frame_buffer,
      sizeof(SATA_FIS_REG_D2H_T) - sizeof(U32)
   );
}