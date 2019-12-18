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
struct strbuf {int dummy; } ;

/* Variables and functions */
 struct strbuf STRBUF_INIT ; 
 int count_slashes (char const*) ; 
 int /*<<< orphan*/  is_dir_sep (char const) ; 
 int /*<<< orphan*/  strbuf_addstr (struct strbuf*,char*) ; 
 char* strbuf_detach (struct strbuf*,int /*<<< orphan*/ *) ; 
 int strlen (char const*) ; 

__attribute__((used)) static char *get_up_path(const char *path)
{
	int i;
	struct strbuf sb = STRBUF_INIT;

	for (i = count_slashes(path); i; i--)
		strbuf_addstr(&sb, "../");

	/*
	 * Check if 'path' ends with slash or not
	 * for having the same output for dir/sub_dir
	 * and dir/sub_dir/
	 */
	if (!is_dir_sep(path[strlen(path) - 1]))
		strbuf_addstr(&sb, "../");

	return strbuf_detach(&sb, NULL);
}