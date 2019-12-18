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
struct bbb_transfer {int /*<<< orphan*/  cv; int /*<<< orphan*/  mtx; int /*<<< orphan*/  xfer; } ;

/* Variables and functions */
 int /*<<< orphan*/  M_USB ; 
 int /*<<< orphan*/  ST_MAX ; 
 int /*<<< orphan*/  cv_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free (struct bbb_transfer*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtx_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  usbd_transfer_unsetup (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
bbb_detach(struct bbb_transfer *sc)
{
	usbd_transfer_unsetup(sc->xfer, ST_MAX);
	mtx_destroy(&sc->mtx);
	cv_destroy(&sc->cv);
	free(sc, M_USB);
}