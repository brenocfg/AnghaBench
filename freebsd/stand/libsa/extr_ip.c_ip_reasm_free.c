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
struct ip_reasm {struct ip_reasm* ip_pkt; struct ip_reasm* ipq_pkt; int /*<<< orphan*/  ip_queue; } ;
struct ip_queue {struct ip_queue* ip_pkt; struct ip_queue* ipq_pkt; int /*<<< orphan*/  ip_queue; } ;

/* Variables and functions */
 struct ip_reasm* STAILQ_FIRST (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  STAILQ_REMOVE_HEAD (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (struct ip_reasm*) ; 
 int /*<<< orphan*/  ipq_next ; 

__attribute__((used)) static void
ip_reasm_free(struct ip_reasm *ipr)
{
	struct ip_queue *ipq;

	while ((ipq = STAILQ_FIRST(&ipr->ip_queue)) != NULL) {
		STAILQ_REMOVE_HEAD(&ipr->ip_queue, ipq_next);
		free(ipq->ipq_pkt);
		free(ipq);
	}
	free(ipr->ip_pkt);
	free(ipr);
}