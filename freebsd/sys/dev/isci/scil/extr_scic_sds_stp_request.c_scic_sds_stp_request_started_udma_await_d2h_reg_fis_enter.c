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
typedef  int /*<<< orphan*/  SCI_BASE_OBJECT_T ;
typedef  int /*<<< orphan*/  SCIC_SDS_REQUEST_T ;

/* Variables and functions */
 int /*<<< orphan*/  SCIC_SDS_STP_REQUEST_STARTED_UDMA_AWAIT_D2H_REG_FIS_SUBSTATE ; 
 int /*<<< orphan*/  SET_STATE_HANDLER (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  scic_sds_stp_request_started_udma_substate_handler_table ; 

__attribute__((used)) static
void scic_sds_stp_request_started_udma_await_d2h_reg_fis_enter(
   SCI_BASE_OBJECT_T *object
)
{
   SCIC_SDS_REQUEST_T *this_request = (SCIC_SDS_REQUEST_T *)object;

   SET_STATE_HANDLER(
      this_request,
      scic_sds_stp_request_started_udma_substate_handler_table,
      SCIC_SDS_STP_REQUEST_STARTED_UDMA_AWAIT_D2H_REG_FIS_SUBSTATE
   );
}