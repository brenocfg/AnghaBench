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
struct ace_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ace_teardown (struct ace_device*) ; 
 int /*<<< orphan*/  dev_dbg (struct device*,char*,struct device*) ; 
 struct ace_device* dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  dev_set_drvdata (struct device*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct ace_device*) ; 

__attribute__((used)) static void ace_free(struct device *dev)
{
	struct ace_device *ace = dev_get_drvdata(dev);
	dev_dbg(dev, "ace_free(%p)\n", dev);

	if (ace) {
		ace_teardown(ace);
		dev_set_drvdata(dev, NULL);
		kfree(ace);
	}
}