#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int u64 ;
struct TYPE_4__ {int /*<<< orphan*/  cs_thres; int /*<<< orphan*/  mode; int /*<<< orphan*/  cscn_en; } ;
struct qm_mcc_initcgr {TYPE_1__ cgr; int /*<<< orphan*/  we_mask; } ;
struct device {int dummy; } ;
typedef  int /*<<< orphan*/  opts ;
struct TYPE_5__ {int /*<<< orphan*/  cgrid; int /*<<< orphan*/  cb; } ;
struct TYPE_6__ {TYPE_2__ cgr; } ;

/* Variables and functions */
 int MAX_RSP_FQ_BACKLOG_PER_CPU ; 
 int /*<<< orphan*/  QMAN_CGR_FLAG_USE_INIT ; 
 int /*<<< orphan*/  QMAN_CGR_MODE_FRAME ; 
 int /*<<< orphan*/  QM_CGR_EN ; 
 int QM_CGR_WE_CSCN_EN ; 
 int QM_CGR_WE_CS_THRES ; 
 int QM_CGR_WE_MODE ; 
 int /*<<< orphan*/  cgr_cb ; 
 int /*<<< orphan*/  cpu_to_be16 (int) ; 
 scalar_t__ cpumask_weight (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_dbg (struct device*,char*,int const) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,int,...) ; 
 int /*<<< orphan*/  memset (struct qm_mcc_initcgr*,int /*<<< orphan*/ ,int) ; 
 TYPE_3__ qipriv ; 
 int /*<<< orphan*/  qm_cgr_cs_thres_set64 (int /*<<< orphan*/ *,int const,int) ; 
 int /*<<< orphan*/  qman_affine_cpus () ; 
 int qman_alloc_cgrid (int /*<<< orphan*/ *) ; 
 int qman_create_cgr (TYPE_2__*,int /*<<< orphan*/ ,struct qm_mcc_initcgr*) ; 

__attribute__((used)) static int init_cgr(struct device *qidev)
{
	int ret;
	struct qm_mcc_initcgr opts;
	const u64 val = (u64)cpumask_weight(qman_affine_cpus()) *
			MAX_RSP_FQ_BACKLOG_PER_CPU;

	ret = qman_alloc_cgrid(&qipriv.cgr.cgrid);
	if (ret) {
		dev_err(qidev, "CGR alloc failed for rsp FQs: %d\n", ret);
		return ret;
	}

	qipriv.cgr.cb = cgr_cb;
	memset(&opts, 0, sizeof(opts));
	opts.we_mask = cpu_to_be16(QM_CGR_WE_CSCN_EN | QM_CGR_WE_CS_THRES |
				   QM_CGR_WE_MODE);
	opts.cgr.cscn_en = QM_CGR_EN;
	opts.cgr.mode = QMAN_CGR_MODE_FRAME;
	qm_cgr_cs_thres_set64(&opts.cgr.cs_thres, val, 1);

	ret = qman_create_cgr(&qipriv.cgr, QMAN_CGR_FLAG_USE_INIT, &opts);
	if (ret) {
		dev_err(qidev, "Error %d creating CAAM CGRID: %u\n", ret,
			qipriv.cgr.cgrid);
		return ret;
	}

	dev_dbg(qidev, "Congestion threshold set to %llu\n", val);
	return 0;
}