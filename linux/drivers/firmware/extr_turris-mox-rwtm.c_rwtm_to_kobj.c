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
struct kobject {int dummy; } ;
struct TYPE_2__ {struct kobject kobj; } ;

/* Variables and functions */

__attribute__((used)) static inline struct kobject *rwtm_to_kobj(struct mox_rwtm *rwtm)
{
	return &rwtm->kobj->kobj;
}