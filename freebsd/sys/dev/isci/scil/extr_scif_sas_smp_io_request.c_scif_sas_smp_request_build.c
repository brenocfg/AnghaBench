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
typedef  int /*<<< orphan*/  SMP_REQUEST_T ;
typedef  int /*<<< orphan*/  SCIF_SAS_REMOTE_DEVICE_T ;
typedef  int /*<<< orphan*/  SCIF_SAS_IO_REQUEST_T ;
typedef  int /*<<< orphan*/  SCIF_SAS_CONTROLLER_T ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SCIF_LOG_ERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SCIF_LOG_OBJECT_IO_REQUEST ; 
 int /*<<< orphan*/  SCI_CONTROLLER_INVALID_IO_TAG ; 
 int /*<<< orphan*/  sci_base_object_get_logger (int /*<<< orphan*/ *) ; 
 void* scif_sas_controller_allocate_internal_request (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  scif_sas_internal_io_request_construct_smp (int /*<<< orphan*/ *,int /*<<< orphan*/ *,void*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  scif_sas_io_request_construct_smp (int /*<<< orphan*/ *,int /*<<< orphan*/ *,void*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,void*) ; 

__attribute__((used)) static
void * scif_sas_smp_request_build(
   SCIF_SAS_CONTROLLER_T    * fw_controller,
   SCIF_SAS_REMOTE_DEVICE_T * fw_device,
   SMP_REQUEST_T            * smp_request,
   void                     * external_request_object,
   void                     * external_memory
)
{
   if (external_memory != NULL && external_request_object != NULL)
   {
      scif_sas_io_request_construct_smp(
         fw_controller,
         fw_device,
         external_memory,
         (char *)external_memory + sizeof(SCIF_SAS_IO_REQUEST_T),
         SCI_CONTROLLER_INVALID_IO_TAG,
         smp_request,
         external_request_object
      );

      return external_memory;
   }
   else
   {
      void * internal_io_memory;
      internal_io_memory = scif_sas_controller_allocate_internal_request(fw_controller);
      ASSERT(internal_io_memory != NULL);

      if (internal_io_memory != NULL)
      {
         //construct, only when we got valid io memory.
         scif_sas_internal_io_request_construct_smp(
            fw_controller,
            fw_device,
            internal_io_memory,
            SCI_CONTROLLER_INVALID_IO_TAG,
            smp_request
         );
      }
      else
      {
         SCIF_LOG_ERROR((
            sci_base_object_get_logger(fw_controller),
            SCIF_LOG_OBJECT_IO_REQUEST,
            "scif_sas_smp_request_build, no memory available!\n"
         ));
      }

      return internal_io_memory;
   }
}