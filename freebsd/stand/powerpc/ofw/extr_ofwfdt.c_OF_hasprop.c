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
 scalar_t__ OF_getproplen (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int
OF_hasprop(phandle_t node, const char *prop)
{
	return (OF_getproplen(node, (char *)prop) > 0);
}