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
struct merge_list {int stage; struct merge_list* link; } ;

/* Variables and functions */

__attribute__((used)) static const char *explanation(struct merge_list *entry)
{
	switch (entry->stage) {
	case 0:
		return "merged";
	case 3:
		return "added in remote";
	case 2:
		if (entry->link)
			return "added in both";
		return "added in local";
	}

	/* Existed in base */
	entry = entry->link;
	if (!entry)
		return "removed in both";

	if (entry->link)
		return "changed in both";

	if (entry->stage == 3)
		return "removed in local";
	return "removed in remote";
}