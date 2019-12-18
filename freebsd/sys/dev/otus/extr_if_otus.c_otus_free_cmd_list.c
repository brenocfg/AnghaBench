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
struct otus_tx_cmd {int /*<<< orphan*/ * buf; } ;
struct otus_softc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  M_USBDEV ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
otus_free_cmd_list(struct otus_softc *sc, struct otus_tx_cmd cmd[], int ndata)
{
	int i;

	/* XXX TODO: someone has to have waken up waiters! */
	for (i = 0; i < ndata; i++) {
		struct otus_tx_cmd *dp = &cmd[i];

		if (dp->buf != NULL) {
			free(dp->buf, M_USBDEV);
			dp->buf = NULL;
		}
	}
}