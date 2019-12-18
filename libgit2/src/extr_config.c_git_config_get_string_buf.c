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
struct TYPE_4__ {char* value; } ;
typedef  TYPE_1__ git_config_entry ;
typedef  int /*<<< orphan*/  git_config ;
typedef  int /*<<< orphan*/  git_buf ;

/* Variables and functions */
 int /*<<< orphan*/  GET_ALL_ERRORS ; 
 int get_entry (TYPE_1__**,int /*<<< orphan*/  const*,char const*,int,int /*<<< orphan*/ ) ; 
 int git_buf_puts (int /*<<< orphan*/ *,char const*) ; 
 int /*<<< orphan*/  git_buf_sanitize (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_config_entry_free (TYPE_1__*) ; 

int git_config_get_string_buf(
	git_buf *out, const git_config *cfg, const char *name)
{
	git_config_entry *entry;
	int ret;
	const char *str;

	git_buf_sanitize(out);

	ret  = get_entry(&entry, cfg, name, true, GET_ALL_ERRORS);
	str = !ret ? (entry->value ? entry->value : "") : NULL;

	if (str)
		ret = git_buf_puts(out, str);

	git_config_entry_free(entry);

	return ret;
}