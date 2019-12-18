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
struct rsu_softc {int dummy; } ;
struct rsu_data {int /*<<< orphan*/ * ni; int /*<<< orphan*/ * buf; } ;

/* Variables and functions */
 int /*<<< orphan*/  M_USBDEV ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ieee80211_free_node (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
rsu_free_list(struct rsu_softc *sc, struct rsu_data data[], int ndata)
{
	int i;

	for (i = 0; i < ndata; i++) {
		struct rsu_data *dp = &data[i];

		if (dp->buf != NULL) {
			free(dp->buf, M_USBDEV);
			dp->buf = NULL;
		}
		if (dp->ni != NULL) {
			ieee80211_free_node(dp->ni);
			dp->ni = NULL;
		}
	}
}