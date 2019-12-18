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
struct dump_obj {int /*<<< orphan*/  buffer; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct dump_obj*) ; 
 struct dump_obj* to_dump_obj (struct kobject*) ; 
 int /*<<< orphan*/  vfree (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void dump_release(struct kobject *kobj)
{
	struct dump_obj *dump;

	dump = to_dump_obj(kobj);
	vfree(dump->buffer);
	kfree(dump);
}