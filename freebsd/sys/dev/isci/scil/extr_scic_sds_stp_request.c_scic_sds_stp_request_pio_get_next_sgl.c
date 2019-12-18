#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_8__ ;
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {scalar_t__ address_lower; scalar_t__ address_upper; } ;
struct TYPE_14__ {scalar_t__ next_pair_lower; scalar_t__ next_pair_upper; TYPE_4__ A; TYPE_4__ B; } ;
struct TYPE_9__ {scalar_t__ sgl_set; TYPE_8__* sgl_pair; } ;
struct TYPE_10__ {TYPE_1__ request_current; int /*<<< orphan*/  sgl_pair_index; } ;
struct TYPE_11__ {TYPE_2__ pio; } ;
struct TYPE_13__ {TYPE_3__ type; int /*<<< orphan*/  parent; } ;
typedef  TYPE_4__ SCU_SGL_ELEMENT_T ;
typedef  TYPE_5__ SCIC_SDS_STP_REQUEST_T ;

/* Variables and functions */
 scalar_t__ SCU_SGL_ELEMENT_PAIR_A ; 
 scalar_t__ SCU_SGL_ELEMENT_PAIR_B ; 
 TYPE_8__* scic_sds_request_get_sgl_element_pair (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

SCU_SGL_ELEMENT_T * scic_sds_stp_request_pio_get_next_sgl(
   SCIC_SDS_STP_REQUEST_T * this_request
)
{
   SCU_SGL_ELEMENT_T * current_sgl;

   if (this_request->type.pio.request_current.sgl_set == SCU_SGL_ELEMENT_PAIR_A)
   {
      if (
            (this_request->type.pio.request_current.sgl_pair->B.address_lower == 0)
         && (this_request->type.pio.request_current.sgl_pair->B.address_upper == 0)
         )
      {
         current_sgl = NULL;
      }
      else
      {
         this_request->type.pio.request_current.sgl_set = SCU_SGL_ELEMENT_PAIR_B;
         current_sgl = &(this_request->type.pio.request_current.sgl_pair->B);
      }
   }
   else
   {
      if (
            (this_request->type.pio.request_current.sgl_pair->next_pair_lower == 0)
         && (this_request->type.pio.request_current.sgl_pair->next_pair_upper == 0)
         )
      {
         current_sgl = NULL;
      }
      else
      {
         this_request->type.pio.request_current.sgl_pair =
            scic_sds_request_get_sgl_element_pair(
               &(this_request->parent),
               ++this_request->type.pio.sgl_pair_index
            );

         this_request->type.pio.request_current.sgl_set = SCU_SGL_ELEMENT_PAIR_A;

         current_sgl = &(this_request->type.pio.request_current.sgl_pair->A);
      }
   }

   return current_sgl;
}