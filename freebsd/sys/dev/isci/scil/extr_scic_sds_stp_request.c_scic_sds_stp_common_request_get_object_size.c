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
typedef  int /*<<< orphan*/  SCIC_SDS_STP_REQUEST_T ;
typedef  int /*<<< orphan*/  SATA_FIS_REG_H2D_T ;
typedef  int /*<<< orphan*/  SATA_FIS_REG_D2H_T ;

/* Variables and functions */
 scalar_t__ CACHE_LINE_SIZE ; 

__attribute__((used)) static
U32 scic_sds_stp_common_request_get_object_size(void)
{
   return   sizeof(SCIC_SDS_STP_REQUEST_T)
          + sizeof(SATA_FIS_REG_H2D_T)
          + sizeof(U32)
          + sizeof(SATA_FIS_REG_D2H_T)
          + sizeof(U32)
          + sizeof(SCU_TASK_CONTEXT_T)
          + CACHE_LINE_SIZE;
}