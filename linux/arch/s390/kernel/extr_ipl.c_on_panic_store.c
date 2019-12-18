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
struct kobject {int dummy; } ;
struct kobj_attribute {int dummy; } ;
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  on_panic_trigger ; 
 int /*<<< orphan*/  set_trigger (char const*,int /*<<< orphan*/ *,size_t) ; 

__attribute__((used)) static ssize_t on_panic_store(struct kobject *kobj,
			      struct kobj_attribute *attr,
			      const char *buf, size_t len)
{
	return set_trigger(buf, &on_panic_trigger, len);
}