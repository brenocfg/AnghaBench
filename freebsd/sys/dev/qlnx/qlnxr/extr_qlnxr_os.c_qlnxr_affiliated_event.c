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
typedef  int u8 ;
typedef  int u64 ;
struct regpair {int lo; scalar_t__ hi; } ;
struct ib_qp {int /*<<< orphan*/  qp_context; int /*<<< orphan*/  (* event_handler ) (struct ib_event*,int /*<<< orphan*/ ) ;int /*<<< orphan*/  device; } ;
struct qlnxr_qp {struct ib_qp ibqp; int /*<<< orphan*/  sig; } ;
struct qlnxr_dev {int /*<<< orphan*/ * ha; } ;
struct ib_cq {int /*<<< orphan*/  cq_context; int /*<<< orphan*/  (* event_handler ) (struct ib_event*,int /*<<< orphan*/ ) ;int /*<<< orphan*/  device; } ;
struct qlnxr_cq {struct ib_cq ibcq; int /*<<< orphan*/  sig; } ;
struct TYPE_2__ {struct ib_qp* qp; struct ib_cq* cq; } ;
struct ib_event {TYPE_1__ element; int /*<<< orphan*/  device; void* event; } ;
typedef  int /*<<< orphan*/  qlnx_host_t ;

/* Variables and functions */
#define  ECORE_IWARP_EVENT_CQ_OVERFLOW 136 
#define  EVENT_TYPE_CQ 135 
#define  EVENT_TYPE_GENERAL 134 
 int EVENT_TYPE_NOT_DEFINED ; 
#define  EVENT_TYPE_QP 133 
 void* IB_EVENT_CQ_ERR ; 
 void* IB_EVENT_QP_ACCESS_ERR ; 
 void* IB_EVENT_QP_FATAL ; 
 void* IB_EVENT_QP_REQ_ERR ; 
 void* IB_EVENT_SQ_DRAINED ; 
 int /*<<< orphan*/  QLNXR_CQ_MAGIC_NUMBER ; 
 int /*<<< orphan*/  QLNXR_QP_MAGIC_NUMBER ; 
 scalar_t__ QLNX_IS_IWARP (struct qlnxr_dev*) ; 
 int /*<<< orphan*/  QL_DPRINT11 (int /*<<< orphan*/ *,char*,int,...) ; 
 int /*<<< orphan*/  QL_DPRINT12 (int /*<<< orphan*/ *,char*,...) ; 
#define  ROCE_ASYNC_EVENT_CQ_OVERFLOW_ERR 132 
#define  ROCE_ASYNC_EVENT_LOCAL_ACCESS_ERR 131 
#define  ROCE_ASYNC_EVENT_LOCAL_INVALID_REQUEST_ERR 130 
#define  ROCE_ASYNC_EVENT_QP_CATASTROPHIC_ERR 129 
#define  ROCE_ASYNC_EVENT_SQ_DRAINED 128 
 int /*<<< orphan*/  stub1 (struct ib_event*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (struct ib_event*,int /*<<< orphan*/ ) ; 

void
qlnxr_affiliated_event(void *context, u8 e_code, void *fw_handle)
{
#define EVENT_TYPE_NOT_DEFINED  0
#define EVENT_TYPE_CQ           1
#define EVENT_TYPE_QP           2
#define EVENT_TYPE_GENERAL      3

        struct qlnxr_dev *dev = (struct qlnxr_dev *)context;
        struct regpair *async_handle = (struct regpair *)fw_handle;
        u64 roceHandle64 = ((u64)async_handle->hi << 32) + async_handle->lo;
        struct qlnxr_cq *cq =  (struct qlnxr_cq *)(uintptr_t)roceHandle64;
        struct qlnxr_qp *qp =  (struct qlnxr_qp *)(uintptr_t)roceHandle64;
        u8 event_type = EVENT_TYPE_NOT_DEFINED;
        struct ib_event event;
	qlnx_host_t *ha;

	ha = dev->ha;

	QL_DPRINT12(ha, "enter context = %p e_code = 0x%x fw_handle = %p\n",
		context, e_code, fw_handle);

        if (QLNX_IS_IWARP(dev)) {
		switch (e_code) {

		case ECORE_IWARP_EVENT_CQ_OVERFLOW:
			event.event = IB_EVENT_CQ_ERR;
			event_type = EVENT_TYPE_CQ;
			break;

		default:
			QL_DPRINT12(ha,
				"unsupported event %d on handle=%llx\n",
				e_code, roceHandle64);
			break;
		}
        } else {
		switch (e_code) {

		case ROCE_ASYNC_EVENT_CQ_OVERFLOW_ERR:
			event.event = IB_EVENT_CQ_ERR;
			event_type = EVENT_TYPE_CQ;
			break;

		case ROCE_ASYNC_EVENT_SQ_DRAINED:
			event.event = IB_EVENT_SQ_DRAINED;
			event_type = EVENT_TYPE_QP;
			break;

		case ROCE_ASYNC_EVENT_QP_CATASTROPHIC_ERR:
			event.event = IB_EVENT_QP_FATAL;
			event_type = EVENT_TYPE_QP;
			break;

		case ROCE_ASYNC_EVENT_LOCAL_INVALID_REQUEST_ERR:
			event.event = IB_EVENT_QP_REQ_ERR;
			event_type = EVENT_TYPE_QP;
			break;

		case ROCE_ASYNC_EVENT_LOCAL_ACCESS_ERR:
			event.event = IB_EVENT_QP_ACCESS_ERR;
			event_type = EVENT_TYPE_QP;
			break;

		/* NOTE the following are not implemented in FW
		 *      ROCE_ASYNC_EVENT_CQ_ERR
		 *      ROCE_ASYNC_EVENT_COMM_EST
		 */
		/* TODO associate the following events -
		 *      ROCE_ASYNC_EVENT_SRQ_LIMIT
		 *      ROCE_ASYNC_EVENT_LAST_WQE_REACHED
		 *      ROCE_ASYNC_EVENT_LOCAL_CATASTROPHIC_ERR (un-affiliated)
		 */
		default:
			QL_DPRINT12(ha,
				"unsupported event 0x%x on fw_handle = %p\n",
				e_code, fw_handle);
			break;
		}
	}

        switch (event_type) {

        case EVENT_TYPE_CQ:
                if (cq && cq->sig == QLNXR_CQ_MAGIC_NUMBER) {
                        struct ib_cq *ibcq = &cq->ibcq;

                        if (ibcq->event_handler) {
                                event.device     = ibcq->device;
                                event.element.cq = ibcq;
                                ibcq->event_handler(&event, ibcq->cq_context);
                        }
                } else {
			QL_DPRINT11(ha,
				"CQ event with invalid CQ pointer"
				" Handle = %llx\n", roceHandle64);
                }
		QL_DPRINT12(ha,
			"CQ event 0x%x on handle = %p\n", e_code, cq);
                break;

        case EVENT_TYPE_QP:
                if (qp && qp->sig == QLNXR_QP_MAGIC_NUMBER) {
                        struct ib_qp *ibqp = &qp->ibqp;

                        if (ibqp->event_handler) {
                                event.device     = ibqp->device;
                                event.element.qp = ibqp;
                                ibqp->event_handler(&event, ibqp->qp_context);
                        }
                } else {
			QL_DPRINT11(ha,
				"QP event 0x%x with invalid QP pointer"
				" qp handle = %p\n",
				e_code, roceHandle64);
                }
		QL_DPRINT12(ha, "QP event 0x%x on qp handle = %p\n",
			e_code, qp);
                break;

        case EVENT_TYPE_GENERAL:
                break;

        default:
                break;

	}

	QL_DPRINT12(ha, "exit\n");

	return;
}