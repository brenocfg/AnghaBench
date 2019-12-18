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
struct rtwn_softc {int dummy; } ;
struct rtwn_data {int /*<<< orphan*/ * m; int /*<<< orphan*/ * ni; int /*<<< orphan*/ * buf; } ;

/* Variables and functions */
 int /*<<< orphan*/  M_USBDEV ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ieee80211_free_node (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  m_freem (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
rtwn_usb_free_list(struct rtwn_softc *sc, struct rtwn_data data[], int ndata)
{
	int i;

	for (i = 0; i < ndata; i++) {
		struct rtwn_data *dp = &data[i];

		if (dp->buf != NULL) {
			free(dp->buf, M_USBDEV);
			dp->buf = NULL;
		}
		if (dp->ni != NULL) {
			ieee80211_free_node(dp->ni);
			dp->ni = NULL;
		}
		if (dp->m != NULL) {
			m_freem(dp->m);
			dp->m = NULL;
		}
	}
}