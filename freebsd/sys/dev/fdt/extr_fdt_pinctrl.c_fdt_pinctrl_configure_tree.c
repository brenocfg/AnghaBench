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
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  OF_peer (int /*<<< orphan*/ ) ; 
 int pinctrl_configure_children (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int
fdt_pinctrl_configure_tree(device_t pinctrl)
{

	return (pinctrl_configure_children(pinctrl, OF_peer(0)));
}