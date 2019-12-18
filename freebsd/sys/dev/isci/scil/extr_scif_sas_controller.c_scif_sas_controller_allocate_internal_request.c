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
struct TYPE_3__ {int /*<<< orphan*/  internal_request_memory_pool; } ;
typedef  TYPE_1__ SCIF_SAS_CONTROLLER_T ;
typedef  scalar_t__ POINTER_UINT ;

/* Variables and functions */
 int /*<<< orphan*/  memset (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sci_pool_empty (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sci_pool_get (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  scif_sas_internal_request_get_object_size () ; 

void * scif_sas_controller_allocate_internal_request(
   SCIF_SAS_CONTROLLER_T * fw_controller
)
{
   POINTER_UINT internal_io_address;

   if( !sci_pool_empty(fw_controller->internal_request_memory_pool) )
   {
      sci_pool_get(
         fw_controller->internal_request_memory_pool, internal_io_address
      );

      //clean the memory.
      memset((char*)internal_io_address, 0, scif_sas_internal_request_get_object_size());

      return (void *) internal_io_address;
   }
   else
      return NULL;
}