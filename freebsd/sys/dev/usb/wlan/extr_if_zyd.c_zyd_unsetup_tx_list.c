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
struct zyd_tx_data {int /*<<< orphan*/ * ni; int /*<<< orphan*/ * m; } ;
struct zyd_softc {struct zyd_tx_data* tx_data; int /*<<< orphan*/  tx_free; int /*<<< orphan*/  tx_q; scalar_t__ tx_nfree; } ;

/* Variables and functions */
 int /*<<< orphan*/  STAILQ_INIT (int /*<<< orphan*/ *) ; 
 int ZYD_TX_LIST_CNT ; 
 int /*<<< orphan*/  ieee80211_free_node (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  m_freem (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
zyd_unsetup_tx_list(struct zyd_softc *sc)
{
	struct zyd_tx_data *data;
	int i;

	/* make sure any subsequent use of the queues will fail */
	sc->tx_nfree = 0;
	STAILQ_INIT(&sc->tx_q);
	STAILQ_INIT(&sc->tx_free);

	/* free up all node references and mbufs */
	for (i = 0; i < ZYD_TX_LIST_CNT; i++) {
		data = &sc->tx_data[i];

		if (data->m != NULL) {
			m_freem(data->m);
			data->m = NULL;
		}
		if (data->ni != NULL) {
			ieee80211_free_node(data->ni);
			data->ni = NULL;
		}
	}
}