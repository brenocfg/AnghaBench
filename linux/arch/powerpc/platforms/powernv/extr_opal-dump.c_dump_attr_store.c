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
struct dump_obj {int dummy; } ;
struct dump_attribute {int /*<<< orphan*/  (* store ) (struct dump_obj*,struct dump_attribute*,char const*,size_t) ;} ;
struct attribute {int dummy; } ;
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  EIO ; 
 int /*<<< orphan*/  stub1 (struct dump_obj*,struct dump_attribute*,char const*,size_t) ; 
 struct dump_attribute* to_dump_attr (struct attribute*) ; 
 struct dump_obj* to_dump_obj (struct kobject*) ; 

__attribute__((used)) static ssize_t dump_attr_store(struct kobject *kobj,
			       struct attribute *attr,
			       const char *buf, size_t len)
{
	struct dump_attribute *attribute;
	struct dump_obj *dump;

	attribute = to_dump_attr(attr);
	dump = to_dump_obj(kobj);

	if (!attribute->store)
		return -EIO;

	return attribute->store(dump, attribute, buf, len);
}