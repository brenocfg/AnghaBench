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

/* Variables and functions */
 int /*<<< orphan*/  config_error_nonbool (char const*) ; 
 int /*<<< orphan*/  display_notes_refs ; 
 int /*<<< orphan*/  strcmp (char const*,char*) ; 
 int /*<<< orphan*/  string_list_add_refs_by_glob (int /*<<< orphan*/ *,char const*) ; 

__attribute__((used)) static int notes_display_config(const char *k, const char *v, void *cb)
{
	int *load_refs = cb;

	if (*load_refs && !strcmp(k, "notes.displayref")) {
		if (!v)
			config_error_nonbool(k);
		string_list_add_refs_by_glob(&display_notes_refs, v);
	}

	return 0;
}