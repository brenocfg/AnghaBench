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
 int /*<<< orphan*/  reipl_block_nss ; 
 int /*<<< orphan*/  reipl_generic_vmparm_store (int /*<<< orphan*/ ,int,char const*,size_t) ; 

__attribute__((used)) static ssize_t reipl_nss_vmparm_store(struct kobject *kobj,
				      struct kobj_attribute *attr,
				      const char *buf, size_t len)
{
	return reipl_generic_vmparm_store(reipl_block_nss, 56, buf, len);
}