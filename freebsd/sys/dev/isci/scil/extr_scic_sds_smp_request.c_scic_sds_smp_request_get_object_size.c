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
typedef  int /*<<< orphan*/  SMP_RESPONSE_T ;
typedef  int /*<<< orphan*/  SMP_REQUEST_T ;
typedef  int /*<<< orphan*/  SCU_TASK_CONTEXT_T ;
typedef  int /*<<< orphan*/  SCIC_SDS_REQUEST_T ;

/* Variables and functions */
 scalar_t__ CACHE_LINE_SIZE ; 

U32 scic_sds_smp_request_get_object_size(void)
{
   return   sizeof(SCIC_SDS_REQUEST_T)
          + sizeof(SMP_REQUEST_T)
          + sizeof(U32)
          + sizeof(SMP_RESPONSE_T)
          + sizeof(U32)
          + sizeof(SCU_TASK_CONTEXT_T)
          + CACHE_LINE_SIZE;
}