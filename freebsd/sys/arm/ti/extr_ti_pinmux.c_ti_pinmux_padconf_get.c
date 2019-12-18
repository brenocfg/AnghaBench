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
typedef  size_t uint16_t ;
struct ti_pinmux_padconf {char** muxmodes; int /*<<< orphan*/  reg_off; } ;
struct TYPE_2__ {size_t padconf_sate_mask; size_t padconf_muxmode_mask; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENXIO ; 
 TYPE_1__* ti_pinmux_dev ; 
 struct ti_pinmux_padconf* ti_pinmux_padconf_from_name (char const*) ; 
 size_t ti_pinmux_read_2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ti_pinmux_sc ; 

int
ti_pinmux_padconf_get(const char *padname, const char **muxmode,
    unsigned int *state)
{
	const struct ti_pinmux_padconf *padconf;
	uint16_t reg_val;

	if (!ti_pinmux_sc)
		return (ENXIO);

	/* find the pin in the devmap */
	padconf = ti_pinmux_padconf_from_name(padname);
	if (padconf == NULL)
		return (EINVAL);

	/* read the register value (16-bit reads) */
	reg_val = ti_pinmux_read_2(ti_pinmux_sc, padconf->reg_off);

	/* save the state */
	if (state)
		*state = (reg_val & ti_pinmux_dev->padconf_sate_mask);

	/* save the mode */
	if (muxmode)
		*muxmode = padconf->muxmodes[(reg_val & ti_pinmux_dev->padconf_muxmode_mask)];

	return (0);
}