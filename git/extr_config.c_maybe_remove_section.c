#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct config_store_data {int* seen; int parsed_nr; int seen_nr; TYPE_1__* parsed; } ;
typedef  enum config_event_t { ____Placeholder_config_event_t } config_event_t ;
struct TYPE_2__ {int type; size_t begin; size_t end; scalar_t__ is_keys_section; } ;

/* Variables and functions */
 int CONFIG_EVENT_COMMENT ; 
 int CONFIG_EVENT_ENTRY ; 
 int CONFIG_EVENT_SECTION ; 

__attribute__((used)) static void maybe_remove_section(struct config_store_data *store,
				 size_t *begin_offset, size_t *end_offset,
				 int *seen_ptr)
{
	size_t begin;
	int i, seen, section_seen = 0;

	/*
	 * First, ensure that this is the first key, and that there are no
	 * comments before the entry nor before the section header.
	 */
	seen = *seen_ptr;
	for (i = store->seen[seen]; i > 0; i--) {
		enum config_event_t type = store->parsed[i - 1].type;

		if (type == CONFIG_EVENT_COMMENT)
			/* There is a comment before this entry or section */
			return;
		if (type == CONFIG_EVENT_ENTRY) {
			if (!section_seen)
				/* This is not the section's first entry. */
				return;
			/* We encountered no comment before the section. */
			break;
		}
		if (type == CONFIG_EVENT_SECTION) {
			if (!store->parsed[i - 1].is_keys_section)
				break;
			section_seen = 1;
		}
	}
	begin = store->parsed[i].begin;

	/*
	 * Next, make sure that we are removing he last key(s) in the section,
	 * and that there are no comments that are possibly about the current
	 * section.
	 */
	for (i = store->seen[seen] + 1; i < store->parsed_nr; i++) {
		enum config_event_t type = store->parsed[i].type;

		if (type == CONFIG_EVENT_COMMENT)
			return;
		if (type == CONFIG_EVENT_SECTION) {
			if (store->parsed[i].is_keys_section)
				continue;
			break;
		}
		if (type == CONFIG_EVENT_ENTRY) {
			if (++seen < store->seen_nr &&
			    i == store->seen[seen])
				/* We want to remove this entry, too */
				continue;
			/* There is another entry in this section. */
			return;
		}
	}

	/*
	 * We are really removing the last entry/entries from this section, and
	 * there are no enclosed or surrounding comments. Remove the entire,
	 * now-empty section.
	 */
	*seen_ptr = seen;
	*begin_offset = begin;
	if (i < store->parsed_nr)
		*end_offset = store->parsed[i].begin;
	else
		*end_offset = store->parsed[store->parsed_nr - 1].end;
}