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
struct urtw_softc {int dummy; } ;
struct urtw_data {int /*<<< orphan*/ * ni; int /*<<< orphan*/ * buf; int /*<<< orphan*/ * m; } ;

/* Variables and functions */
 int /*<<< orphan*/  ieee80211_free_node (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  m_freem (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
urtw_free_data_list(struct urtw_softc *sc, struct urtw_data data[], int ndata,
    int fillmbuf)
{
	int i;

	for (i = 0; i < ndata; i++) {
		struct urtw_data *dp = &data[i];

		if (fillmbuf == 1) {
			if (dp->m != NULL) {
				m_freem(dp->m);
				dp->m = NULL;
				dp->buf = NULL;
			}
		} else {
			dp->buf = NULL;
		}
		if (dp->ni != NULL) {
			ieee80211_free_node(dp->ni);
			dp->ni = NULL;
		}
	}
}