#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_5__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/ * fqs; int /*<<< orphan*/  ern; } ;
struct qman_fq {int /*<<< orphan*/  fqid; TYPE_1__ cb; } ;
struct TYPE_8__ {int /*<<< orphan*/  cgid; int /*<<< orphan*/  context_b; void* fq_ctrl; } ;
struct qm_mcc_initfq {TYPE_3__ fqd; void* we_mask; } ;
struct device {int dummy; } ;
typedef  int /*<<< orphan*/  opts ;
typedef  int /*<<< orphan*/  dma_addr_t ;
struct TYPE_7__ {int /*<<< orphan*/  cgrid; } ;
struct TYPE_9__ {TYPE_2__ cgr; } ;

/* Variables and functions */
 int ENOMEM ; 
 struct qman_fq* ERR_PTR (int) ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int QMAN_FQ_FLAG_DYNAMIC_FQID ; 
 int QMAN_FQ_FLAG_TO_DCPORTAL ; 
 int QM_FQCTRL_CGE ; 
 int QM_FQCTRL_CPCSTASH ; 
 int QM_INITFQ_WE_CGID ; 
 int QM_INITFQ_WE_CONTEXTA ; 
 int QM_INITFQ_WE_CONTEXTB ; 
 int QM_INITFQ_WE_DESTWQ ; 
 int QM_INITFQ_WE_FQCTRL ; 
 int /*<<< orphan*/  caam_fq_ern_cb ; 
 void* cpu_to_be16 (int) ; 
 int /*<<< orphan*/  cpu_to_be32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_dbg (struct device*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*) ; 
 int /*<<< orphan*/  kfree (struct qman_fq*) ; 
 struct qman_fq* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct qm_mcc_initfq*,int /*<<< orphan*/ ,int) ; 
 TYPE_5__ qipriv ; 
 int /*<<< orphan*/  qm_channel_caam ; 
 int /*<<< orphan*/  qm_fqd_context_a_set64 (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qm_fqd_set_destwq (TYPE_3__*,int /*<<< orphan*/ ,int) ; 
 int qman_create_fq (int /*<<< orphan*/ ,int,struct qman_fq*) ; 
 int /*<<< orphan*/  qman_destroy_fq (struct qman_fq*) ; 
 int /*<<< orphan*/  qman_fq_fqid (struct qman_fq*) ; 
 int qman_init_fq (struct qman_fq*,int,struct qm_mcc_initfq*) ; 
 int /*<<< orphan*/  smp_processor_id () ; 

__attribute__((used)) static struct qman_fq *create_caam_req_fq(struct device *qidev,
					  struct qman_fq *rsp_fq,
					  dma_addr_t hwdesc,
					  int fq_sched_flag)
{
	int ret;
	struct qman_fq *req_fq;
	struct qm_mcc_initfq opts;

	req_fq = kzalloc(sizeof(*req_fq), GFP_ATOMIC);
	if (!req_fq)
		return ERR_PTR(-ENOMEM);

	req_fq->cb.ern = caam_fq_ern_cb;
	req_fq->cb.fqs = NULL;

	ret = qman_create_fq(0, QMAN_FQ_FLAG_DYNAMIC_FQID |
				QMAN_FQ_FLAG_TO_DCPORTAL, req_fq);
	if (ret) {
		dev_err(qidev, "Failed to create session req FQ\n");
		goto create_req_fq_fail;
	}

	memset(&opts, 0, sizeof(opts));
	opts.we_mask = cpu_to_be16(QM_INITFQ_WE_FQCTRL | QM_INITFQ_WE_DESTWQ |
				   QM_INITFQ_WE_CONTEXTB |
				   QM_INITFQ_WE_CONTEXTA | QM_INITFQ_WE_CGID);
	opts.fqd.fq_ctrl = cpu_to_be16(QM_FQCTRL_CPCSTASH | QM_FQCTRL_CGE);
	qm_fqd_set_destwq(&opts.fqd, qm_channel_caam, 2);
	opts.fqd.context_b = cpu_to_be32(qman_fq_fqid(rsp_fq));
	qm_fqd_context_a_set64(&opts.fqd, hwdesc);
	opts.fqd.cgid = qipriv.cgr.cgrid;

	ret = qman_init_fq(req_fq, fq_sched_flag, &opts);
	if (ret) {
		dev_err(qidev, "Failed to init session req FQ\n");
		goto init_req_fq_fail;
	}

	dev_dbg(qidev, "Allocated request FQ %u for CPU %u\n", req_fq->fqid,
		smp_processor_id());
	return req_fq;

init_req_fq_fail:
	qman_destroy_fq(req_fq);
create_req_fq_fail:
	kfree(req_fq);
	return ERR_PTR(ret);
}