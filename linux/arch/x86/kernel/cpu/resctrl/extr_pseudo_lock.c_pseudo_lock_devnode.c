#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int umode_t ;
struct rdtgroup {TYPE_1__* kn; } ;
struct device {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 struct rdtgroup* dev_get_drvdata (struct device*) ; 
 char* kasprintf (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static char *pseudo_lock_devnode(struct device *dev, umode_t *mode)
{
	struct rdtgroup *rdtgrp;

	rdtgrp = dev_get_drvdata(dev);
	if (mode)
		*mode = 0600;
	return kasprintf(GFP_KERNEL, "pseudo_lock/%s", rdtgrp->kn->name);
}