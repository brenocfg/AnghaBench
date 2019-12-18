#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct as3722_softc {int dummy; } ;
struct TYPE_3__ {int fnc_val; int /*<<< orphan*/  name; } ;

/* Variables and functions */
 TYPE_1__* as3722_fnc_table ; 
 int nitems (TYPE_1__*) ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int
as3722_pinmux_get_function(struct as3722_softc *sc, char *name)
{
	int i;

	for (i = 0; i < nitems(as3722_fnc_table); i++) {
		if (strcmp(as3722_fnc_table[i].name, name) == 0)
			 return (as3722_fnc_table[i].fnc_val);
	}
	return (-1);
}