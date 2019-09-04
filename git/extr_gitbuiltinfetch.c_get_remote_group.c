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
struct remote_group_data {int /*<<< orphan*/  list; int /*<<< orphan*/  name; } ;

/* Variables and functions */
 scalar_t__ skip_prefix (char const*,char*,char const**) ; 
 int /*<<< orphan*/  strcmp (char const*,int /*<<< orphan*/ ) ; 
 size_t strcspn (char const*,char*) ; 
 int /*<<< orphan*/  string_list_append_nodup (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xstrndup (char const*,size_t) ; 

__attribute__((used)) static int get_remote_group(const char *key, const char *value, void *priv)
{
	struct remote_group_data *g = priv;

	if (skip_prefix(key, "remotes.", &key) && !strcmp(key, g->name)) {
		/* split list by white space */
		while (*value) {
			size_t wordlen = strcspn(value, " \t\n");

			if (wordlen >= 1)
				string_list_append_nodup(g->list,
						   xstrndup(value, wordlen));
			value += wordlen + (value[wordlen] != '\0');
		}
	}

	return 0;
}