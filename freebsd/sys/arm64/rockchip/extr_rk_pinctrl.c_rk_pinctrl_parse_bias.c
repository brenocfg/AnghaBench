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
typedef  int /*<<< orphan*/  phandle_t ;

/* Variables and functions */
 scalar_t__ OF_hasprop (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int
rk_pinctrl_parse_bias(phandle_t node)
{
	if (OF_hasprop(node, "bias-disable"))
		return (0);
	if (OF_hasprop(node, "bias-pull-up"))
		return (1);
	if (OF_hasprop(node, "bias-pull-down"))
		return (2);

	return (-1);
}