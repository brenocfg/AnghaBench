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
struct qrange {int dummy; } ;
struct qout64 {unsigned long qoutptr; int qoutlen; int segcnt; int segstart; TYPE_1__* range; int /*<<< orphan*/  segend; int /*<<< orphan*/  qname; int /*<<< orphan*/  qopcode; } ;
struct qin64 {unsigned long qoutptr; int qoutlen; int segcnt; int segstart; TYPE_1__* range; int /*<<< orphan*/  segend; int /*<<< orphan*/  qname; int /*<<< orphan*/  qopcode; } ;
struct dcss_segment {int vm_segtype; int start_addr; int segcnt; int /*<<< orphan*/  range; int /*<<< orphan*/  end; TYPE_1__* dcss_name; } ;
struct TYPE_2__ {int start; int end; } ;

/* Variables and functions */
 int /*<<< orphan*/  DCSS_FINDSEGA ; 
 int ENOMEM ; 
 int EOPNOTSUPP ; 
 int GFP_DMA ; 
 int GFP_KERNEL ; 
 int PAGE_SHIFT ; 
 int SEG_TYPE_EN ; 
 int SEG_TYPE_EW ; 
 int SEG_TYPE_EWEN ; 
 int dcss_diag (int /*<<< orphan*/ *,struct qout64*,unsigned long*,unsigned long*) ; 
 int dcss_diag_translate_rc (unsigned long) ; 
 int /*<<< orphan*/  kfree (struct qout64*) ; 
 struct qout64* kmalloc (int,int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,TYPE_1__*,int) ; 
 int /*<<< orphan*/  pr_warn (char*,unsigned long) ; 
 int /*<<< orphan*/  segext_scode ; 

__attribute__((used)) static int
query_segment_type (struct dcss_segment *seg)
{
	unsigned long dummy, vmrc;
	int diag_cc, rc, i;
	struct qout64 *qout;
	struct qin64 *qin;

	qin = kmalloc(sizeof(*qin), GFP_KERNEL | GFP_DMA);
	qout = kmalloc(sizeof(*qout), GFP_KERNEL | GFP_DMA);
	if ((qin == NULL) || (qout == NULL)) {
		rc = -ENOMEM;
		goto out_free;
	}

	/* initialize diag input parameters */
	qin->qopcode = DCSS_FINDSEGA;
	qin->qoutptr = (unsigned long) qout;
	qin->qoutlen = sizeof(struct qout64);
	memcpy (qin->qname, seg->dcss_name, 8);

	diag_cc = dcss_diag(&segext_scode, qin, &dummy, &vmrc);

	if (diag_cc < 0) {
		rc = diag_cc;
		goto out_free;
	}
	if (diag_cc > 1) {
		pr_warn("Querying a DCSS type failed with rc=%ld\n", vmrc);
		rc = dcss_diag_translate_rc (vmrc);
		goto out_free;
	}

	if (qout->segcnt > 6) {
		rc = -EOPNOTSUPP;
		goto out_free;
	}

	if (qout->segcnt == 1) {
		seg->vm_segtype = qout->range[0].start & 0xff;
	} else {
		/* multi-part segment. only one type supported here:
		    - all parts are contiguous
		    - all parts are either EW or EN type
		    - maximum 6 parts allowed */
		unsigned long start = qout->segstart >> PAGE_SHIFT;
		for (i=0; i<qout->segcnt; i++) {
			if (((qout->range[i].start & 0xff) != SEG_TYPE_EW) &&
			    ((qout->range[i].start & 0xff) != SEG_TYPE_EN)) {
				rc = -EOPNOTSUPP;
				goto out_free;
			}
			if (start != qout->range[i].start >> PAGE_SHIFT) {
				rc = -EOPNOTSUPP;
				goto out_free;
			}
			start = (qout->range[i].end >> PAGE_SHIFT) + 1;
		}
		seg->vm_segtype = SEG_TYPE_EWEN;
	}

	/* analyze diag output and update seg */
	seg->start_addr = qout->segstart;
	seg->end = qout->segend;

	memcpy (seg->range, qout->range, 6*sizeof(struct qrange));
	seg->segcnt = qout->segcnt;

	rc = 0;

 out_free:
	kfree(qin);
	kfree(qout);
	return rc;
}