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
struct threshold_block {int dummy; } ;
struct threshold_attr {int /*<<< orphan*/  (* store ) (struct threshold_block*,char const*,size_t) ;} ;
struct kobject {int dummy; } ;
struct attribute {int dummy; } ;
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  EIO ; 
 int /*<<< orphan*/  stub1 (struct threshold_block*,char const*,size_t) ; 
 struct threshold_attr* to_attr (struct attribute*) ; 
 struct threshold_block* to_block (struct kobject*) ; 

__attribute__((used)) static ssize_t store(struct kobject *kobj, struct attribute *attr,
		     const char *buf, size_t count)
{
	struct threshold_block *b = to_block(kobj);
	struct threshold_attr *a = to_attr(attr);
	ssize_t ret;

	ret = a->store ? a->store(b, buf, count) : -EIO;

	return ret;
}