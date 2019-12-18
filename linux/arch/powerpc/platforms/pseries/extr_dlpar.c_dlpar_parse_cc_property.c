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
struct property {int length; int /*<<< orphan*/  value; int /*<<< orphan*/  name; } ;
struct cc_workarea {int /*<<< orphan*/  prop_offset; int /*<<< orphan*/  prop_length; int /*<<< orphan*/  name_offset; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int be32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dlpar_free_cc_property (struct property*) ; 
 int /*<<< orphan*/  kmemdup (char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kstrdup (char*,int /*<<< orphan*/ ) ; 
 struct property* kzalloc (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct property *dlpar_parse_cc_property(struct cc_workarea *ccwa)
{
	struct property *prop;
	char *name;
	char *value;

	prop = kzalloc(sizeof(*prop), GFP_KERNEL);
	if (!prop)
		return NULL;

	name = (char *)ccwa + be32_to_cpu(ccwa->name_offset);
	prop->name = kstrdup(name, GFP_KERNEL);
	if (!prop->name) {
		dlpar_free_cc_property(prop);
		return NULL;
	}

	prop->length = be32_to_cpu(ccwa->prop_length);
	value = (char *)ccwa + be32_to_cpu(ccwa->prop_offset);
	prop->value = kmemdup(value, prop->length, GFP_KERNEL);
	if (!prop->value) {
		dlpar_free_cc_property(prop);
		return NULL;
	}

	return prop;
}