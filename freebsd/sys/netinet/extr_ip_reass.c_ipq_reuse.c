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
struct mbuf {struct mbuf* m_nextpkt; } ;
struct ipq {struct mbuf* ipq_frags; int /*<<< orphan*/  ipq_nfrags; } ;
struct TYPE_2__ {int /*<<< orphan*/  count; int /*<<< orphan*/  head; } ;

/* Variables and functions */
 int /*<<< orphan*/  IPQ_LOCK_ASSERT (int) ; 
 scalar_t__ IPQ_TRYLOCK (int) ; 
 int /*<<< orphan*/  IPQ_UNLOCK (int) ; 
 int IPREASS_NHASH ; 
 int /*<<< orphan*/  IPSTAT_ADD (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct ipq* TAILQ_LAST (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TAILQ_REMOVE (int /*<<< orphan*/ *,struct ipq*,int /*<<< orphan*/ ) ; 
 TYPE_1__* V_ipq ; 
 int /*<<< orphan*/  atomic_subtract_int (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ipq_list ; 
 int /*<<< orphan*/  ipqhead ; 
 int /*<<< orphan*/  ips_fragtimeout ; 
 int /*<<< orphan*/  m_freem (struct mbuf*) ; 
 int /*<<< orphan*/  nfrags ; 

__attribute__((used)) static struct ipq *
ipq_reuse(int start)
{
	struct ipq *fp;
	int bucket, i;

	IPQ_LOCK_ASSERT(start);

	for (i = 0; i < IPREASS_NHASH; i++) {
		bucket = (start + i) % IPREASS_NHASH;
		if (bucket != start && IPQ_TRYLOCK(bucket) == 0)
			continue;
		fp = TAILQ_LAST(&V_ipq[bucket].head, ipqhead);
		if (fp) {
			struct mbuf *m;

			IPSTAT_ADD(ips_fragtimeout, fp->ipq_nfrags);
			atomic_subtract_int(&nfrags, fp->ipq_nfrags);
			while (fp->ipq_frags) {
				m = fp->ipq_frags;
				fp->ipq_frags = m->m_nextpkt;
				m_freem(m);
			}
			TAILQ_REMOVE(&V_ipq[bucket].head, fp, ipq_list);
			V_ipq[bucket].count--;
			if (bucket != start)
				IPQ_UNLOCK(bucket);
			break;
		}
		if (bucket != start)
			IPQ_UNLOCK(bucket);
	}
	IPQ_LOCK_ASSERT(start);
	return (fp);
}