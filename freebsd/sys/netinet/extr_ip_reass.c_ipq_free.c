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
struct mbuf {struct mbuf* m_nextpkt; } ;
struct ipqbucket {int /*<<< orphan*/  count; int /*<<< orphan*/  head; } ;
struct ipq {struct mbuf* ipq_frags; int /*<<< orphan*/  ipq_nfrags; } ;

/* Variables and functions */
 int /*<<< orphan*/  TAILQ_REMOVE (int /*<<< orphan*/ *,struct ipq*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  V_ipq_zone ; 
 int /*<<< orphan*/  atomic_subtract_int (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ipq_list ; 
 int /*<<< orphan*/  m_freem (struct mbuf*) ; 
 int /*<<< orphan*/  nfrags ; 
 int /*<<< orphan*/  uma_zfree (int /*<<< orphan*/ ,struct ipq*) ; 

__attribute__((used)) static void
ipq_free(struct ipqbucket *bucket, struct ipq *fp)
{
	struct mbuf *q;

	atomic_subtract_int(&nfrags, fp->ipq_nfrags);
	while (fp->ipq_frags) {
		q = fp->ipq_frags;
		fp->ipq_frags = q->m_nextpkt;
		m_freem(q);
	}
	TAILQ_REMOVE(&bucket->head, fp, ipq_list);
	bucket->count--;
	uma_zfree(V_ipq_zone, fp);
}