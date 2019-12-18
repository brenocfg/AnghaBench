#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  len; } ;
struct mbuf {TYPE_2__ m_pkthdr; struct mbuf* m_nextpkt; } ;
struct m_tag {int dummy; } ;
struct TYPE_8__ {scalar_t__ length; } ;
struct TYPE_9__ {int /*<<< orphan*/  q_time; TYPE_3__ ni; } ;
struct fq_pie_si {TYPE_4__ main_q; } ;
struct TYPE_6__ {struct mbuf* head; } ;
struct fq_pie_flow {TYPE_1__ mq; } ;
typedef  int /*<<< orphan*/  aqm_time_t ;
struct TYPE_10__ {int /*<<< orphan*/  curr_time; } ;

/* Variables and functions */
 int /*<<< orphan*/  D (char*) ; 
 int /*<<< orphan*/  DN_AQM_MTAG_TS ; 
 int /*<<< orphan*/  MTAG_ABI_COMPAT ; 
 TYPE_5__ dn_cfg ; 
 int /*<<< orphan*/  fq_update_stats (struct fq_pie_flow*,struct fq_pie_si*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  m_tag_delete (struct mbuf*,struct m_tag*) ; 
 struct m_tag* m_tag_locate (struct mbuf*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) __inline static struct mbuf *
fq_pie_extract_head(struct fq_pie_flow *q, aqm_time_t *pkt_ts,
	struct fq_pie_si *si, int getts)
{
	struct mbuf *m = q->mq.head;

	if (m == NULL)
		return m;
	q->mq.head = m->m_nextpkt;

	fq_update_stats(q, si, -m->m_pkthdr.len, 0);

	if (si->main_q.ni.length == 0) /* queue is now idle */
			si->main_q.q_time = dn_cfg.curr_time;

	if (getts) {
		/* extract packet timestamp*/
		struct m_tag *mtag;
		mtag = m_tag_locate(m, MTAG_ABI_COMPAT, DN_AQM_MTAG_TS, NULL);
		if (mtag == NULL){
			D("PIE timestamp mtag not found!");
			*pkt_ts = 0;
		} else {
			*pkt_ts = *(aqm_time_t *)(mtag + 1);
			m_tag_delete(m,mtag); 
		}
	}
	return m;
}