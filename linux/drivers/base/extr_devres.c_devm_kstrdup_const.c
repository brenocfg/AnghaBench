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
struct device {int dummy; } ;
typedef  int /*<<< orphan*/  gfp_t ;

/* Variables and functions */
 char const* devm_kstrdup (struct device*,char const*,int /*<<< orphan*/ ) ; 
 scalar_t__ is_kernel_rodata (unsigned long) ; 

const char *devm_kstrdup_const(struct device *dev, const char *s, gfp_t gfp)
{
	if (is_kernel_rodata((unsigned long)s))
		return s;

	return devm_kstrdup(dev, s, gfp);
}