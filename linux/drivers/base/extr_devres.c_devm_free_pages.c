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
struct pages_devres {unsigned long addr; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  WARN_ON (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  devm_pages_match ; 
 int /*<<< orphan*/  devm_pages_release ; 
 int /*<<< orphan*/  devres_release (struct device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct pages_devres*) ; 

void devm_free_pages(struct device *dev, unsigned long addr)
{
	struct pages_devres devres = { .addr = addr };

	WARN_ON(devres_release(dev, devm_pages_release, devm_pages_match,
			       &devres));
}