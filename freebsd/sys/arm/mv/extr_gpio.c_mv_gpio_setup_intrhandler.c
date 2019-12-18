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
struct mv_gpio_softc {int pin_num; struct intr_event** gpio_events; TYPE_1__* gpio_setup; } ;
struct mv_gpio_pindev {int dummy; } ;
struct intr_event {int dummy; } ;
typedef  int /*<<< orphan*/  driver_filter_t ;
typedef  int /*<<< orphan*/  device_t ;
struct TYPE_2__ {int gp_flags; } ;

/* Variables and functions */
 int ENXIO ; 
 int MV_GPIO_IN_DEBOUNCE ; 
 int MV_GPIO_IN_IRQ_DOUBLE_EDGE ; 
 int /*<<< orphan*/  MV_GPIO_LOCK () ; 
 int /*<<< orphan*/  MV_GPIO_UNLOCK () ; 
 int /*<<< orphan*/  M_DEVBUF ; 
 int M_NOWAIT ; 
 int M_ZERO ; 
 scalar_t__ device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  intr_event_add_handler (struct intr_event*,char const*,int /*<<< orphan*/ *,void (*) (void*),void*,int /*<<< orphan*/ ,int,void**) ; 
 int intr_event_create (struct intr_event**,void*,int /*<<< orphan*/ ,int,void (*) (void*),void (*) (void*),void (*) (void*),int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  intr_priority (int) ; 
 struct mv_gpio_pindev* malloc (int,int /*<<< orphan*/ ,int) ; 
 int mv_gpio_debounce_init (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mv_gpio_double_edge_init (int /*<<< orphan*/ ,int) ; 
 scalar_t__ mv_gpio_int_ack ; 
 scalar_t__ mv_gpio_intr_mask ; 
 scalar_t__ mv_gpio_intr_unmask ; 

int
mv_gpio_setup_intrhandler(device_t dev, const char *name, driver_filter_t *filt,
    void (*hand)(void *), void *arg, int pin, int flags, void **cookiep)
{
	struct	intr_event *event;
	int	error;
	struct mv_gpio_pindev *s;
	struct mv_gpio_softc *sc;
	sc = (struct mv_gpio_softc *)device_get_softc(dev);
	s = malloc(sizeof(struct mv_gpio_pindev), M_DEVBUF, M_NOWAIT | M_ZERO);

	if (pin < 0 || pin >= sc->pin_num)
		return (ENXIO);
	event = sc->gpio_events[pin];
	if (event == NULL) {
		MV_GPIO_LOCK();
		if (sc->gpio_setup[pin].gp_flags & MV_GPIO_IN_DEBOUNCE) {
			error = mv_gpio_debounce_init(dev, pin);
			if (error != 0) {
				MV_GPIO_UNLOCK();
				return (error);
			}
		} else if (sc->gpio_setup[pin].gp_flags & MV_GPIO_IN_IRQ_DOUBLE_EDGE)
			mv_gpio_double_edge_init(dev, pin);
		MV_GPIO_UNLOCK();
		error = intr_event_create(&event, (void *)s, 0, pin,
		    (void (*)(void *))mv_gpio_intr_mask,
		    (void (*)(void *))mv_gpio_intr_unmask,
		    (void (*)(void *))mv_gpio_int_ack,
		    NULL,
		    "gpio%d:", pin);
		if (error != 0)
			return (error);
		sc->gpio_events[pin] = event;
	}

	intr_event_add_handler(event, name, filt, hand, arg,
	    intr_priority(flags), flags, cookiep);
	return (0);
}