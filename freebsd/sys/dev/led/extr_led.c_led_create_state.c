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
struct ledsc {struct cdev* dev; void* private; int /*<<< orphan*/  (* func ) (void*,int) ;int /*<<< orphan*/  unit; int /*<<< orphan*/  name; } ;
struct cdev {struct ledsc* si_drv1; } ;
typedef  int /*<<< orphan*/  (* led_t ) (void*,int) ;

/* Variables and functions */
 int /*<<< orphan*/  GID_WHEEL ; 
 int /*<<< orphan*/  LIST_INSERT_HEAD (int /*<<< orphan*/ *,struct ledsc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  M_LED ; 
 int M_WAITOK ; 
 int M_ZERO ; 
 int /*<<< orphan*/  UID_ROOT ; 
 int /*<<< orphan*/  alloc_unr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  led_cdevsw ; 
 int /*<<< orphan*/  led_list ; 
 int /*<<< orphan*/  led_mtx ; 
 int /*<<< orphan*/  led_sx ; 
 int /*<<< orphan*/  led_unit ; 
 int /*<<< orphan*/  list ; 
 struct cdev* make_dev (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,char*,char const*) ; 
 struct ledsc* malloc (int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strdup (char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (void*,int) ; 
 int /*<<< orphan*/  sx_xlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sx_xunlock (int /*<<< orphan*/ *) ; 

struct cdev *
led_create_state(led_t *func, void *priv, char const *name, int state)
{
	struct ledsc	*sc;

	sc = malloc(sizeof *sc, M_LED, M_WAITOK | M_ZERO);

	sx_xlock(&led_sx);
	sc->name = strdup(name, M_LED);
	sc->unit = alloc_unr(led_unit);
	sc->private = priv;
	sc->func = func;
	sc->dev = make_dev(&led_cdevsw, sc->unit,
	    UID_ROOT, GID_WHEEL, 0600, "led/%s", name);
	sx_xunlock(&led_sx);

	mtx_lock(&led_mtx);
	sc->dev->si_drv1 = sc;
	LIST_INSERT_HEAD(&led_list, sc, list);
	if (state != -1)
		sc->func(sc->private, state != 0);
	mtx_unlock(&led_mtx);

	return (sc->dev);
}