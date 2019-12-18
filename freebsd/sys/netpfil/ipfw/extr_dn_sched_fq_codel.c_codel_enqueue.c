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
typedef  scalar_t__ uint64_t ;
struct TYPE_4__ {scalar_t__ len; } ;
struct mbuf {TYPE_2__ m_pkthdr; } ;
struct m_tag {int dummy; } ;
struct fq_codel_si {int dummy; } ;
struct TYPE_3__ {scalar_t__ maxpkt_size; } ;
struct fq_codel_flow {int /*<<< orphan*/  mq; TYPE_1__ cst; } ;
typedef  int /*<<< orphan*/  aqm_time_t ;

/* Variables and functions */
 int /*<<< orphan*/  AQM_UNOW ; 
 int /*<<< orphan*/  DN_AQM_MTAG_TS ; 
 int /*<<< orphan*/  MTAG_ABI_COMPAT ; 
 int /*<<< orphan*/  M_NOWAIT ; 
 int /*<<< orphan*/  fq_update_stats (struct fq_codel_flow*,struct fq_codel_si*,scalar_t__,int) ; 
 int /*<<< orphan*/  m_freem (struct mbuf*) ; 
 struct m_tag* m_tag_alloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 struct m_tag* m_tag_locate (struct mbuf*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  m_tag_prepend (struct mbuf*,struct m_tag*) ; 
 int /*<<< orphan*/  mq_append (int /*<<< orphan*/ *,struct mbuf*) ; 

__attribute__((used)) static int
codel_enqueue(struct fq_codel_flow *q, struct mbuf *m, struct fq_codel_si *si)
{
	uint64_t len;

	len = m->m_pkthdr.len;
	/* finding maximum packet size */
	if (len > q->cst.maxpkt_size)
		q->cst.maxpkt_size = len;

	/* Add timestamp to mbuf as MTAG */
	struct m_tag *mtag;
	mtag = m_tag_locate(m, MTAG_ABI_COMPAT, DN_AQM_MTAG_TS, NULL);
	if (mtag == NULL)
		mtag = m_tag_alloc(MTAG_ABI_COMPAT, DN_AQM_MTAG_TS, sizeof(aqm_time_t),
			M_NOWAIT);
	if (mtag == NULL) {
		m_freem(m); 
		goto drop;
	}
	*(aqm_time_t *)(mtag + 1) = AQM_UNOW;
	m_tag_prepend(m, mtag);

	mq_append(&q->mq, m);
	fq_update_stats(q, si, len, 0);
	return 0;

drop:
	fq_update_stats(q, si, len, 1);
	m_freem(m);
	return 1;
}