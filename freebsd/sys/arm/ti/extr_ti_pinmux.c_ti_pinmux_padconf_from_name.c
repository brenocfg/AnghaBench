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
struct ti_pinmux_padconf {int /*<<< orphan*/ * ballname; } ;
struct TYPE_2__ {struct ti_pinmux_padconf* padconf; } ;

/* Variables and functions */
 scalar_t__ strcmp (char const*,int /*<<< orphan*/ *) ; 
 TYPE_1__* ti_pinmux_dev ; 

__attribute__((used)) static const struct ti_pinmux_padconf*
ti_pinmux_padconf_from_name(const char *ballname)
{
	const struct ti_pinmux_padconf *padconf;

	padconf = ti_pinmux_dev->padconf;
	while (padconf->ballname != NULL) {
		if (strcmp(ballname, padconf->ballname) == 0)
			return(padconf);
		padconf++;
	}

	return (NULL);
}