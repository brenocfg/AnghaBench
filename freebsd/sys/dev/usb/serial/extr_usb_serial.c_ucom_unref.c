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
struct ucom_super_softc {int sc_refs; } ;

/* Variables and functions */
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ucom_free_unit (struct ucom_super_softc*) ; 
 int /*<<< orphan*/  ucom_mtx ; 

int
ucom_unref(struct ucom_super_softc *ssc)
{
	int retval;

	mtx_lock(&ucom_mtx);
	retval = (ssc->sc_refs < 2);
	ssc->sc_refs--;
	mtx_unlock(&ucom_mtx);

	if (retval)
		ucom_free_unit(ssc);

	return (retval);
}