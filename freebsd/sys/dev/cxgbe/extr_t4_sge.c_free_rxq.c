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
struct vi_info {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/ * ifp; } ;
struct sge_rxq {int /*<<< orphan*/  fl; int /*<<< orphan*/  iq; TYPE_1__ lro; } ;

/* Variables and functions */
 int /*<<< orphan*/  bzero (struct sge_rxq*,int) ; 
 int free_iq_fl (struct vi_info*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tcp_lro_free (TYPE_1__*) ; 

__attribute__((used)) static int
free_rxq(struct vi_info *vi, struct sge_rxq *rxq)
{
	int rc;

#if defined(INET) || defined(INET6)
	if (rxq->lro.ifp) {
		tcp_lro_free(&rxq->lro);
		rxq->lro.ifp = NULL;
	}
#endif

	rc = free_iq_fl(vi, &rxq->iq, &rxq->fl);
	if (rc == 0)
		bzero(rxq, sizeof(*rxq));

	return (rc);
}