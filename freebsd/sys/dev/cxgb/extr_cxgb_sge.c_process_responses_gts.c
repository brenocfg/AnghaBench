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
struct sge_rspq {int next_holdoff; int /*<<< orphan*/  cidx; int /*<<< orphan*/  cntxt_id; } ;
typedef  int /*<<< orphan*/  adapter_t ;

/* Variables and functions */
 int /*<<< orphan*/  A_SG_GTS ; 
 int V_NEWINDEX (int /*<<< orphan*/ ) ; 
 int V_NEWTIMER (int) ; 
 int V_RSPQ (int /*<<< orphan*/ ) ; 
 scalar_t__ cxgb_debug ; 
 int /*<<< orphan*/  printf (char*,int) ; 
 int process_responses (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  rspq_to_qset (struct sge_rspq*) ; 
 int /*<<< orphan*/  t3_write_reg (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static __inline int
process_responses_gts(adapter_t *adap, struct sge_rspq *rq)
{
	int work;
	static int last_holdoff = 0;
	
	work = process_responses(adap, rspq_to_qset(rq), -1);

	if (cxgb_debug && (rq->next_holdoff != last_holdoff)) {
		printf("next_holdoff=%d\n", rq->next_holdoff);
		last_holdoff = rq->next_holdoff;
	}
	t3_write_reg(adap, A_SG_GTS, V_RSPQ(rq->cntxt_id) |
	    V_NEWTIMER(rq->next_holdoff) | V_NEWINDEX(rq->cidx));
	
	return (work);
}