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
struct pt_iscache_lru_entry {int /*<<< orphan*/  section; struct pt_iscache_lru_entry* next; } ;

/* Variables and functions */
 int /*<<< orphan*/  free (struct pt_iscache_lru_entry*) ; 
 int pt_section_unmap (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int pt_iscache_lru_free(struct pt_iscache_lru_entry *lru)
{
	while (lru) {
		struct pt_iscache_lru_entry *trash;
		int errcode;

		trash = lru;
		lru = lru->next;

		errcode = pt_section_unmap(trash->section);
		if (errcode < 0)
			return errcode;

		free(trash);
	}

	return 0;
}