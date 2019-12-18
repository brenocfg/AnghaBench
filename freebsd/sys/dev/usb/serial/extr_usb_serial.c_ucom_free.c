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
struct ucom_softc {int /*<<< orphan*/  sc_super; TYPE_1__* sc_callback; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* ucom_free ) (struct ucom_softc*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (struct ucom_softc*) ; 
 int /*<<< orphan*/  ucom_close_refs ; 
 int /*<<< orphan*/  ucom_mtx ; 
 int /*<<< orphan*/  ucom_unref (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
ucom_free(void *xsc)
{
	struct ucom_softc *sc = xsc;

	if (sc->sc_callback->ucom_free != NULL)
		sc->sc_callback->ucom_free(sc);
	else
		ucom_unref(sc->sc_super);

	mtx_lock(&ucom_mtx);
	ucom_close_refs--;
	mtx_unlock(&ucom_mtx);
}