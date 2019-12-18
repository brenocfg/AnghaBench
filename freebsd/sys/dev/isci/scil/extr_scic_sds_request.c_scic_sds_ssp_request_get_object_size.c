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
typedef  int /*<<< orphan*/  SCU_TASK_CONTEXT_T ;
typedef  int /*<<< orphan*/  SCU_SGL_ELEMENT_PAIR_T ;
typedef  int /*<<< orphan*/  SCIC_SDS_REQUEST_T ;

/* Variables and functions */
 scalar_t__ CACHE_LINE_SIZE ; 
 int SCU_MAX_SGL_ELEMENT_PAIRS ; 
 scalar_t__ scic_ssp_io_request_get_object_size () ; 

__attribute__((used)) static
U32 scic_sds_ssp_request_get_object_size(void)
{
   return   sizeof(SCIC_SDS_REQUEST_T)
          + scic_ssp_io_request_get_object_size()
          + sizeof(SCU_TASK_CONTEXT_T)
          + CACHE_LINE_SIZE
          + sizeof(SCU_SGL_ELEMENT_PAIR_T) * SCU_MAX_SGL_ELEMENT_PAIRS;
}