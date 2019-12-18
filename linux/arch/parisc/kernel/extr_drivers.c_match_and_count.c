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
struct parisc_device {int dummy; } ;
struct match_count {int /*<<< orphan*/  count; int /*<<< orphan*/  driver; } ;
struct device {int dummy; } ;

/* Variables and functions */
 scalar_t__ check_dev (struct device*) ; 
 scalar_t__ match_device (int /*<<< orphan*/ ,struct parisc_device*) ; 
 struct parisc_device* to_parisc_device (struct device*) ; 

__attribute__((used)) static int match_and_count(struct device * dev, void * data)
{
	struct match_count * m = data;
	struct parisc_device * pdev = to_parisc_device(dev);

	if (check_dev(dev)) {
		if (match_device(m->driver, pdev))
			m->count++;
	}
	return 0;
}