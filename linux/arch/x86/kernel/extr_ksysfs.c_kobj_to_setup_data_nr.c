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

/* Variables and functions */
 char* kobject_name (struct kobject*) ; 
 int kstrtoint (char const*,int,int*) ; 

__attribute__((used)) static int kobj_to_setup_data_nr(struct kobject *kobj, int *nr)
{
	const char *name;

	name = kobject_name(kobj);
	return kstrtoint(name, 10, nr);
}