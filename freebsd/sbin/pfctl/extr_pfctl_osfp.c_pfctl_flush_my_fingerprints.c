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
struct name_list {int dummy; } ;
struct name_entry {struct name_list nm_sublist; } ;

/* Variables and functions */
 struct name_entry* LIST_FIRST (struct name_list*) ; 
 int /*<<< orphan*/  LIST_REMOVE (struct name_entry*,int /*<<< orphan*/ ) ; 
 scalar_t__ class_count ; 
 scalar_t__ fingerprint_count ; 
 int /*<<< orphan*/  free (struct name_entry*) ; 
 int /*<<< orphan*/  nm_entry ; 

void
pfctl_flush_my_fingerprints(struct name_list *list)
{
	struct name_entry *nm;

	while ((nm = LIST_FIRST(list)) != NULL) {
		LIST_REMOVE(nm, nm_entry);
		pfctl_flush_my_fingerprints(&nm->nm_sublist);
		free(nm);
	}
	fingerprint_count = 0;
	class_count = 0;
}