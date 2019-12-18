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
struct switch_attrlist {int n_attr; struct switch_attr const* attr; } ;
struct switch_attr {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 scalar_t__ strcmp (char const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static const struct switch_attr *
swconfig_find_attr_by_name(const struct switch_attrlist *alist,
				const char *name)
{
	int i;

	for (i = 0; i < alist->n_attr; i++)
		if (strcmp(name, alist->attr[i].name) == 0)
			return &alist->attr[i];

	return NULL;
}