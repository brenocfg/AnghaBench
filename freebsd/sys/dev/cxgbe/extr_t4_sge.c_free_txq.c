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
struct vi_info {TYPE_1__* pi; } ;
struct sge_eq {int dummy; } ;
struct sge_txq {int /*<<< orphan*/  r; int /*<<< orphan*/  sdesc; int /*<<< orphan*/  gl; struct sge_eq eq; } ;
struct adapter {int dummy; } ;
struct TYPE_2__ {struct adapter* adapter; } ;

/* Variables and functions */
 int /*<<< orphan*/  M_CXGBE ; 
 int /*<<< orphan*/  bzero (struct sge_txq*,int) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int free_eq (struct adapter*,struct sge_eq*) ; 
 int /*<<< orphan*/  mp_ring_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sglist_free (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
free_txq(struct vi_info *vi, struct sge_txq *txq)
{
	int rc;
	struct adapter *sc = vi->pi->adapter;
	struct sge_eq *eq = &txq->eq;

	rc = free_eq(sc, eq);
	if (rc)
		return (rc);

	sglist_free(txq->gl);
	free(txq->sdesc, M_CXGBE);
	mp_ring_free(txq->r);

	bzero(txq, sizeof(*txq));
	return (0);
}