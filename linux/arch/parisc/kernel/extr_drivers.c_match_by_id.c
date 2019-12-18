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
struct parisc_device {scalar_t__ hw_path; } ;
struct match_id_data {scalar_t__ id; struct parisc_device* dev; } ;
struct device {int dummy; } ;

/* Variables and functions */
 struct parisc_device* to_parisc_device (struct device*) ; 

__attribute__((used)) static int match_by_id(struct device * dev, void * data)
{
	struct parisc_device * pdev = to_parisc_device(dev);
	struct match_id_data * d = data;

	if (pdev->hw_path == d->id) {
		d->dev = pdev;
		return 1;
	}
	return 0;
}