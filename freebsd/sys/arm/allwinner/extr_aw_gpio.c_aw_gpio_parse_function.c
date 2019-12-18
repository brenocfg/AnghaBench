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
 int OF_getprop_alloc (int /*<<< orphan*/ ,char*,void**) ; 

__attribute__((used)) static char *
aw_gpio_parse_function(phandle_t node)
{
	char *function;

	if (OF_getprop_alloc(node, "function",
	    (void **)&function) != -1)
		return (function);
	if (OF_getprop_alloc(node, "allwinner,function",
	    (void **)&function) != -1)
		return (function);

	return (NULL);
}