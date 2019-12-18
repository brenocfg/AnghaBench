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
typedef  scalar_t__ U32 ;
typedef  int /*<<< orphan*/  SCU_SGL_ELEMENT_PAIR_T ;

/* Variables and functions */
 int SCU_MAX_SGL_ELEMENT_PAIRS ; 
 scalar_t__ scic_sds_stp_common_request_get_object_size () ; 

U32 scic_sds_stp_request_get_object_size(void)
{
   return   scic_sds_stp_common_request_get_object_size()
          + sizeof(SCU_SGL_ELEMENT_PAIR_T) * SCU_MAX_SGL_ELEMENT_PAIRS;
}