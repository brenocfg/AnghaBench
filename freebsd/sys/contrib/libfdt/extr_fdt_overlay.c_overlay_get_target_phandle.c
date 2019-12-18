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
typedef  int /*<<< orphan*/  fdt32_t ;

/* Variables and functions */
 scalar_t__ fdt32_to_cpu (int /*<<< orphan*/  const) ; 
 int /*<<< orphan*/ * fdt_getprop (void const*,int,char*,int*) ; 

__attribute__((used)) static uint32_t overlay_get_target_phandle(const void *fdto, int fragment)
{
	const fdt32_t *val;
	int len;

	val = fdt_getprop(fdto, fragment, "target", &len);
	if (!val)
		return 0;

	if ((len != sizeof(*val)) || (fdt32_to_cpu(*val) == (uint32_t)-1))
		return (uint32_t)-1;

	return fdt32_to_cpu(*val);
}