#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint32_t ;
struct qfq_sched {scalar_t__ wsum; scalar_t__ iwsum; int /*<<< orphan*/ * groups; } ;
struct qfq_class {scalar_t__ lmax; scalar_t__ inv_w; int /*<<< orphan*/ * grp; } ;
struct dn_queue {TYPE_2__* fs; scalar_t__ _si; } ;
struct TYPE_3__ {scalar_t__* par; } ;
struct TYPE_4__ {TYPE_1__ fs; } ;

/* Variables and functions */
 int /*<<< orphan*/  D (char*) ; 
 int EINVAL ; 
 scalar_t__ ONE_FP ; 
 scalar_t__ QFQ_MAX_WEIGHT ; 
 scalar_t__ QFQ_MAX_WSUM ; 
 int qfq_calc_index (scalar_t__,scalar_t__) ; 

__attribute__((used)) static int
qfq_new_queue(struct dn_queue *_q)
{
	struct qfq_sched *q = (struct qfq_sched *)(_q->_si + 1);
	struct qfq_class *cl = (struct qfq_class *)_q;
	int i;
	uint32_t w;	/* approximated weight */

	/* import parameters from the flowset. They should be correct
	 * already.
	 */
	w = _q->fs->fs.par[0];
	cl->lmax = _q->fs->fs.par[1];
	if (!w || w > QFQ_MAX_WEIGHT) {
		w = 1;
		D("rounding weight to 1");
	}
	cl->inv_w = ONE_FP/w;
	w = ONE_FP/cl->inv_w;	
	if (q->wsum + w > QFQ_MAX_WSUM)
		return EINVAL;

	i = qfq_calc_index(cl->inv_w, cl->lmax);
	cl->grp = &q->groups[i];
	q->wsum += w;
	q->iwsum = ONE_FP / q->wsum; /* XXX note theory */
	// XXX cl->S = q->V; ?
	return 0;
}