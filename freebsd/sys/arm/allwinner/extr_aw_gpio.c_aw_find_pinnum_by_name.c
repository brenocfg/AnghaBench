#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct aw_gpio_softc {TYPE_2__* padconf; } ;
struct TYPE_4__ {int npins; TYPE_1__* pins; } ;
struct TYPE_3__ {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  strcmp (char const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
aw_find_pinnum_by_name(struct aw_gpio_softc *sc, const char *pinname)
{
	int i;

	for (i = 0; i < sc->padconf->npins; i++)
		if (!strcmp(pinname, sc->padconf->pins[i].name))
			return i;

	return (-1);
}