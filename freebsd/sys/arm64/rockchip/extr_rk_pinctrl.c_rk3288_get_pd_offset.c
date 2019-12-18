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
typedef  scalar_t__ uint32_t ;
struct rk_pinctrl_softc {int dummy; } ;

/* Variables and functions */

__attribute__((used)) static uint32_t
rk3288_get_pd_offset(struct rk_pinctrl_softc *sc, uint32_t bank)
{
	if (bank == 0)
		return (0x064);		/* PMU */
	return (0x130);
}