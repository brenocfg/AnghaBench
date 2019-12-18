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
typedef  int /*<<< orphan*/  SCI_LIBRARY_HANDLE_T ;

/* Variables and functions */
 int /*<<< orphan*/  SCU_IO_REQUEST_SGE_COUNT ; 

U32 scic_library_get_max_sge_count(
   SCI_LIBRARY_HANDLE_T library
)
{
   return SCU_IO_REQUEST_SGE_COUNT;
}