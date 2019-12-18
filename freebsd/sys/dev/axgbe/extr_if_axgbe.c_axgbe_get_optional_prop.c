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
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int ENXIO ; 
 scalar_t__ OF_getencprop (int /*<<< orphan*/ ,char const*,int*,size_t) ; 
 int /*<<< orphan*/  OF_hasprop (int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,char const*) ; 

__attribute__((used)) static int
axgbe_get_optional_prop(device_t dev, phandle_t node, const char *name,
    int *data, size_t len)
{

	if (!OF_hasprop(node, name))
		return (-1);

	if (OF_getencprop(node, name, data, len) <= 0) {
		device_printf(dev,"%s property is invalid\n", name);
		return (ENXIO);
	}

	return (0);
}