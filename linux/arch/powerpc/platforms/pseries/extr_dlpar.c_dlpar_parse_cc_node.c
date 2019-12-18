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
struct device_node {int /*<<< orphan*/  full_name; } ;
struct cc_workarea {int /*<<< orphan*/  name_offset; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  OF_DYNAMIC ; 
 int be32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct device_node*) ; 
 int /*<<< orphan*/  kstrdup (char const*,int /*<<< orphan*/ ) ; 
 struct device_node* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  of_node_init (struct device_node*) ; 
 int /*<<< orphan*/  of_node_set_flag (struct device_node*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct device_node *dlpar_parse_cc_node(struct cc_workarea *ccwa)
{
	struct device_node *dn;
	const char *name;

	dn = kzalloc(sizeof(*dn), GFP_KERNEL);
	if (!dn)
		return NULL;

	name = (const char *)ccwa + be32_to_cpu(ccwa->name_offset);
	dn->full_name = kstrdup(name, GFP_KERNEL);
	if (!dn->full_name) {
		kfree(dn);
		return NULL;
	}

	of_node_set_flag(dn, OF_DYNAMIC);
	of_node_init(dn);

	return dn;
}