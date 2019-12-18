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
struct kobj_uevent_env {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  type; int /*<<< orphan*/  vendor; } ;
struct fsl_mc_device {TYPE_1__ obj_desc; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 
 scalar_t__ add_uevent_var (struct kobj_uevent_env*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct fsl_mc_device* to_fsl_mc_device (struct device*) ; 

__attribute__((used)) static int fsl_mc_bus_uevent(struct device *dev, struct kobj_uevent_env *env)
{
	struct fsl_mc_device *mc_dev = to_fsl_mc_device(dev);

	if (add_uevent_var(env, "MODALIAS=fsl-mc:v%08Xd%s",
			   mc_dev->obj_desc.vendor,
			   mc_dev->obj_desc.type))
		return -ENOMEM;

	return 0;
}