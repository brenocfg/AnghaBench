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
struct ledsc {struct ledsc* name; int /*<<< orphan*/ * spec; int /*<<< orphan*/  unit; int /*<<< orphan*/ * ptr; } ;
struct cdev {struct ledsc* si_drv1; } ;

/* Variables and functions */
 scalar_t__ LIST_EMPTY (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  LIST_REMOVE (struct ledsc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  M_LED ; 
 int /*<<< orphan*/  blinkers ; 
 int /*<<< orphan*/  callout_stop (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  destroy_dev (struct cdev*) ; 
 int /*<<< orphan*/  free (struct ledsc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free_unr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  led_ch ; 
 int /*<<< orphan*/  led_list ; 
 int /*<<< orphan*/  led_mtx ; 
 int /*<<< orphan*/  led_sx ; 
 int /*<<< orphan*/  led_unit ; 
 int /*<<< orphan*/  list ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sbuf_delete (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sx_xlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sx_xunlock (int /*<<< orphan*/ *) ; 

void
led_destroy(struct cdev *dev)
{
	struct ledsc *sc;

	mtx_lock(&led_mtx);
	sc = dev->si_drv1;
	dev->si_drv1 = NULL;
	if (sc->ptr != NULL)
		blinkers--;
	LIST_REMOVE(sc, list);
	if (LIST_EMPTY(&led_list))
		callout_stop(&led_ch);
	mtx_unlock(&led_mtx);

	sx_xlock(&led_sx);
	free_unr(led_unit, sc->unit);
	destroy_dev(dev);
	if (sc->spec != NULL)
		sbuf_delete(sc->spec);
	free(sc->name, M_LED);
	free(sc, M_LED);
	sx_xunlock(&led_sx);
}