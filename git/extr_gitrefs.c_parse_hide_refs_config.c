#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int strdup_strings; } ;

/* Variables and functions */
 int config_error_nonbool (char const*) ; 
 TYPE_1__* hide_refs ; 
 int /*<<< orphan*/  parse_config_key (char const*,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,char const**) ; 
 int /*<<< orphan*/  strcmp (char const*,char const*) ; 
 int /*<<< orphan*/  string_list_append (TYPE_1__*,char*) ; 
 int strlen (char*) ; 
 TYPE_1__* xcalloc (int,int) ; 
 char* xstrdup (char const*) ; 

int parse_hide_refs_config(const char *var, const char *value, const char *section)
{
	const char *key;
	if (!strcmp("transfer.hiderefs", var) ||
	    (!parse_config_key(var, section, NULL, NULL, &key) &&
	     !strcmp(key, "hiderefs"))) {
		char *ref;
		int len;

		if (!value)
			return config_error_nonbool(var);
		ref = xstrdup(value);
		len = strlen(ref);
		while (len && ref[len - 1] == '/')
			ref[--len] = '\0';
		if (!hide_refs) {
			hide_refs = xcalloc(1, sizeof(*hide_refs));
			hide_refs->strdup_strings = 1;
		}
		string_list_append(hide_refs, ref);
	}
	return 0;
}