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
typedef  int /*<<< orphan*/  SCIF_SAS_TASK_REQUEST_T ;
typedef  int /*<<< orphan*/  SCIF_SAS_INTERNAL_IO_REQUEST_T ;

/* Variables and functions */
 int /*<<< orphan*/  MAX (scalar_t__,scalar_t__) ; 
 scalar_t__ scic_io_request_get_object_size () ; 
 scalar_t__ scic_task_request_get_object_size () ; 

U32 scif_sas_internal_request_get_object_size(
   void
)
{
   return MAX(
            (sizeof(SCIF_SAS_INTERNAL_IO_REQUEST_T) + scic_io_request_get_object_size()),
            (sizeof(SCIF_SAS_TASK_REQUEST_T) + scic_task_request_get_object_size())
             );
}