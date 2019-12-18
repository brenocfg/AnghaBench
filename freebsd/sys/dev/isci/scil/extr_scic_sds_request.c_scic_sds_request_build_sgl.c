#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ U32 ;
struct TYPE_4__ {scalar_t__ next_pair_lower; scalar_t__ next_pair_upper; int /*<<< orphan*/  B; int /*<<< orphan*/  A; } ;
typedef  TYPE_1__ SCU_SGL_ELEMENT_PAIR_T ;
typedef  int /*<<< orphan*/  SCI_PHYSICAL_ADDRESS ;
typedef  int /*<<< orphan*/  SCIC_SDS_REQUEST_T ;

/* Variables and functions */
 int /*<<< orphan*/  SCU_SGL_COPY (void*,int /*<<< orphan*/ ,void*) ; 
 int /*<<< orphan*/  SCU_SGL_ZERO (int /*<<< orphan*/ ) ; 
 scalar_t__ sci_cb_physical_address_lower (int /*<<< orphan*/ ) ; 
 scalar_t__ sci_cb_physical_address_upper (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  scic_cb_io_request_get_next_sge (void*,void*,void**) ; 
 int /*<<< orphan*/  scic_cb_io_request_get_physical_address (int /*<<< orphan*/ ,int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  scic_sds_request_get_controller (int /*<<< orphan*/ *) ; 
 TYPE_1__* scic_sds_request_get_sgl_element_pair (int /*<<< orphan*/ *,scalar_t__) ; 
 void* scic_sds_request_get_user_request (int /*<<< orphan*/ *) ; 

void scic_sds_request_build_sgl(
   SCIC_SDS_REQUEST_T *this_request
)
{
   void                   *os_sge;
   void                   *os_handle;
   SCI_PHYSICAL_ADDRESS    physical_address;
   U32                     sgl_pair_index = 0;
   SCU_SGL_ELEMENT_PAIR_T *scu_sgl_list   = NULL;
   SCU_SGL_ELEMENT_PAIR_T *previous_pair  = NULL;

   os_handle = scic_sds_request_get_user_request(this_request);
   scic_cb_io_request_get_next_sge(os_handle, NULL, &os_sge);

   while (os_sge != NULL)
   {
      scu_sgl_list =
         scic_sds_request_get_sgl_element_pair(this_request, sgl_pair_index);

      SCU_SGL_COPY(os_handle, scu_sgl_list->A, os_sge);

      scic_cb_io_request_get_next_sge(os_handle, os_sge, &os_sge);

      if (os_sge != NULL)
      {
         SCU_SGL_COPY(os_handle, scu_sgl_list->B, os_sge);

         scic_cb_io_request_get_next_sge(os_handle, os_sge, &os_sge);
      }
      else
      {
         SCU_SGL_ZERO(scu_sgl_list->B);
      }

      if (previous_pair != NULL)
      {
         scic_cb_io_request_get_physical_address(
            scic_sds_request_get_controller(this_request),
            this_request,
            scu_sgl_list,
            &physical_address
         );

         previous_pair->next_pair_upper =
            sci_cb_physical_address_upper(physical_address);
         previous_pair->next_pair_lower =
            sci_cb_physical_address_lower(physical_address);
      }

      previous_pair = scu_sgl_list;
      sgl_pair_index++;
   }

   if (scu_sgl_list != NULL)
   {
      scu_sgl_list->next_pair_upper = 0;
      scu_sgl_list->next_pair_lower = 0;
   }
}