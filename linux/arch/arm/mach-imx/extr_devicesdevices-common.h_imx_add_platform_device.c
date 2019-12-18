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
struct resource {int dummy; } ;
struct platform_device {int dummy; } ;

/* Variables and functions */
 struct platform_device* imx_add_platform_device_dmamask (char const*,int,struct resource const*,unsigned int,void const*,size_t,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline struct platform_device *imx_add_platform_device(
		const char *name, int id,
		const struct resource *res, unsigned int num_resources,
		const void *data, size_t size_data)
{
	return imx_add_platform_device_dmamask(
			name, id, res, num_resources, data, size_data, 0);
}