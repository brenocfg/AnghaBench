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
struct run_tx_data {struct run_softc* sc; } ;
struct run_softc {int dummy; } ;
struct run_endpoint_queue {size_t tx_nfree; int /*<<< orphan*/  tx_fh; struct run_tx_data* tx_data; int /*<<< orphan*/  tx_qh; } ;

/* Variables and functions */
 size_t RUN_TX_RING_COUNT ; 
 int /*<<< orphan*/  STAILQ_INIT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  STAILQ_INSERT_TAIL (int /*<<< orphan*/ *,struct run_tx_data*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct run_endpoint_queue*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  next ; 

__attribute__((used)) static void
run_setup_tx_list(struct run_softc *sc, struct run_endpoint_queue *pq)
{
	struct run_tx_data *data;

	memset(pq, 0, sizeof(*pq));

	STAILQ_INIT(&pq->tx_qh);
	STAILQ_INIT(&pq->tx_fh);

	for (data = &pq->tx_data[0];
	    data < &pq->tx_data[RUN_TX_RING_COUNT]; data++) {
		data->sc = sc;
		STAILQ_INSERT_TAIL(&pq->tx_fh, data, next);
	}
	pq->tx_nfree = RUN_TX_RING_COUNT;
}