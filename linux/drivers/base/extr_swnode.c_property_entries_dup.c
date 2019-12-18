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
struct property_entry {scalar_t__ name; } ;

/* Variables and functions */
 int ENOMEM ; 
 struct property_entry* ERR_PTR (int) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 struct property_entry* kcalloc (int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct property_entry*) ; 
 int property_entry_copy_data (struct property_entry*,struct property_entry const*) ; 
 int /*<<< orphan*/  property_entry_free_data (struct property_entry*) ; 

struct property_entry *
property_entries_dup(const struct property_entry *properties)
{
	struct property_entry *p;
	int i, n = 0;
	int ret;

	if (!properties)
		return NULL;

	while (properties[n].name)
		n++;

	p = kcalloc(n + 1, sizeof(*p), GFP_KERNEL);
	if (!p)
		return ERR_PTR(-ENOMEM);

	for (i = 0; i < n; i++) {
		ret = property_entry_copy_data(&p[i], &properties[i]);
		if (ret) {
			while (--i >= 0)
				property_entry_free_data(&p[i]);
			kfree(p);
			return ERR_PTR(ret);
		}
	}

	return p;
}