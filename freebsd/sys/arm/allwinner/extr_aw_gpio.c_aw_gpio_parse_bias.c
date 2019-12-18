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
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int /*<<< orphan*/  phandle_t ;
typedef  int /*<<< orphan*/  bias ;

/* Variables and functions */
 int /*<<< orphan*/  AW_GPIO_NONE ; 
 int /*<<< orphan*/  AW_GPIO_PULLDOWN ; 
 int /*<<< orphan*/  AW_GPIO_PULLUP ; 
 int OF_getencprop (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *,int) ; 
 scalar_t__ OF_hasprop (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static uint32_t
aw_gpio_parse_bias(phandle_t node)
{
	uint32_t bias;

	if (OF_getencprop(node, "pull", &bias, sizeof(bias)) != -1)
		return (bias);
	if (OF_getencprop(node, "allwinner,pull", &bias, sizeof(bias)) != -1)
		return (bias);
	if (OF_hasprop(node, "bias-disable"))
		return (AW_GPIO_NONE);
	if (OF_hasprop(node, "bias-pull-up"))
		return (AW_GPIO_PULLUP);
	if (OF_hasprop(node, "bias-pull-down"))
		return (AW_GPIO_PULLDOWN);

	return (AW_GPIO_NONE);
}