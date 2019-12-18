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
struct rtwn_softc {int /*<<< orphan*/  sc_dev; } ;
struct rtwn_data {int /*<<< orphan*/ * ni; int /*<<< orphan*/ * buf; int /*<<< orphan*/ * m; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  M_NOWAIT ; 
 int /*<<< orphan*/  M_USBDEV ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/ * malloc (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtwn_usb_free_list (struct rtwn_softc*,struct rtwn_data*,int) ; 

__attribute__((used)) static int
rtwn_usb_alloc_list(struct rtwn_softc *sc, struct rtwn_data data[],
    int ndata, int maxsz)
{
	int i, error;

	for (i = 0; i < ndata; i++) {
		struct rtwn_data *dp = &data[i];
		dp->m = NULL;
		dp->buf = malloc(maxsz, M_USBDEV, M_NOWAIT);
		if (dp->buf == NULL) {
			device_printf(sc->sc_dev,
			    "could not allocate buffer\n");
			error = ENOMEM;
			goto fail;
		}
		dp->ni = NULL;
	}

	return (0);
fail:
	rtwn_usb_free_list(sc, data, ndata);
	return (error);
}