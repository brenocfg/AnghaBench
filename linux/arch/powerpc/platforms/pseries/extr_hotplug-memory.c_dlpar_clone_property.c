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
typedef  int u32 ;
struct property {int length; void* value; int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  OF_DYNAMIC ; 
 int /*<<< orphan*/  dlpar_free_property (struct property*) ; 
 int /*<<< orphan*/  kstrdup (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 void* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (void*,void*,int) ; 
 int /*<<< orphan*/  of_property_set_flag (struct property*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct property *dlpar_clone_property(struct property *prop,
					     u32 prop_size)
{
	struct property *new_prop;

	new_prop = kzalloc(sizeof(*new_prop), GFP_KERNEL);
	if (!new_prop)
		return NULL;

	new_prop->name = kstrdup(prop->name, GFP_KERNEL);
	new_prop->value = kzalloc(prop_size, GFP_KERNEL);
	if (!new_prop->name || !new_prop->value) {
		dlpar_free_property(new_prop);
		return NULL;
	}

	memcpy(new_prop->value, prop->value, prop->length);
	new_prop->length = prop_size;

	of_property_set_flag(new_prop, OF_DYNAMIC);
	return new_prop;
}