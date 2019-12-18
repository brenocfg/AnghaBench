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
struct upgt_softc {struct upgt_data* sc_rx_data; } ;
struct upgt_data {int /*<<< orphan*/ * ni; int /*<<< orphan*/ * buf; } ;

/* Variables and functions */
 int UPGT_RX_MAXCOUNT ; 

__attribute__((used)) static void
upgt_free_rx(struct upgt_softc *sc)
{
	int i;

	for (i = 0; i < UPGT_RX_MAXCOUNT; i++) {
		struct upgt_data *data = &sc->sc_rx_data[i];

		data->buf = NULL;
		data->ni = NULL;
	}
}