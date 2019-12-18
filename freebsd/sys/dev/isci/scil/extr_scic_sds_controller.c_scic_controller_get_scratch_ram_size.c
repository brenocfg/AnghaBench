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
typedef  int /*<<< orphan*/  SCI_CONTROLLER_HANDLE_T ;

/* Variables and functions */
 int /*<<< orphan*/  SCU_SCRATCH_RAM_SIZE_IN_DWORDS ; 

U32 scic_controller_get_scratch_ram_size(
   SCI_CONTROLLER_HANDLE_T   controller
)
{
   return SCU_SCRATCH_RAM_SIZE_IN_DWORDS;
}