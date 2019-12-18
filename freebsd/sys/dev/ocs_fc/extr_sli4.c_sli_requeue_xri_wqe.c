#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  void* uint16_t ;
typedef  int /*<<< orphan*/  sli4_t ;
struct TYPE_2__ {int xc; int qosd; int /*<<< orphan*/  cmd_type; void* cq_id; void* request_tag; void* xri_tag; int /*<<< orphan*/  command; } ;
typedef  TYPE_1__ sli4_requeue_xri_wqe_t ;
typedef  int /*<<< orphan*/  int32_t ;

/* Variables and functions */
 int /*<<< orphan*/  SLI4_CMD_REQUEUE_XRI_WQE ; 
 int /*<<< orphan*/  SLI4_WQE_REQUEUE_XRI ; 
 int /*<<< orphan*/  ocs_memset (void*,int /*<<< orphan*/ ,size_t) ; 

int32_t
sli_requeue_xri_wqe(sli4_t *sli4, void *buf, size_t size, uint16_t xri, uint16_t tag, uint16_t cq_id)
{
	sli4_requeue_xri_wqe_t	*requeue = buf;

	ocs_memset(buf, 0, size);

	requeue->command = SLI4_WQE_REQUEUE_XRI;
	requeue->xri_tag = xri;
	requeue->request_tag = tag;
	requeue->xc = 1;
	requeue->qosd = 1;
	requeue->cq_id = cq_id;
	requeue->cmd_type = SLI4_CMD_REQUEUE_XRI_WQE;
	return 0;
}