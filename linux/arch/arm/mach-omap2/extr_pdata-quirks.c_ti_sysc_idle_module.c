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
struct ti_sysc_cookie {int /*<<< orphan*/  data; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int omap_hwmod_idle (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ti_sysc_idle_module(struct device *dev,
			       const struct ti_sysc_cookie *cookie)
{
	if (!cookie->data)
		return -EINVAL;

	return omap_hwmod_idle(cookie->data);
}