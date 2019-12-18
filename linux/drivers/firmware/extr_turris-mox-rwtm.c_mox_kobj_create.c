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
struct mox_rwtm {TYPE_1__* kobj; } ;
struct TYPE_2__ {struct mox_rwtm* rwtm; } ;

/* Variables and functions */
 int ENOMEM ; 
 int ENXIO ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  firmware_kobj ; 
 scalar_t__ kobject_add (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  kobject_init (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kobject_put (int /*<<< orphan*/ ) ; 
 TYPE_1__* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mox_kobj_ktype ; 
 int /*<<< orphan*/  rwtm_to_kobj (struct mox_rwtm*) ; 

__attribute__((used)) static int mox_kobj_create(struct mox_rwtm *rwtm)
{
	rwtm->kobj = kzalloc(sizeof(*rwtm->kobj), GFP_KERNEL);
	if (!rwtm->kobj)
		return -ENOMEM;

	kobject_init(rwtm_to_kobj(rwtm), &mox_kobj_ktype);
	if (kobject_add(rwtm_to_kobj(rwtm), firmware_kobj, "turris-mox-rwtm")) {
		kobject_put(rwtm_to_kobj(rwtm));
		return -ENXIO;
	}

	rwtm->kobj->rwtm = rwtm;

	return 0;
}