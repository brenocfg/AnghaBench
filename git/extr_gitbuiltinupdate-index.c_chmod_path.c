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
struct cache_entry {int dummy; } ;

/* Variables and functions */
 struct cache_entry** active_cache ; 
 int cache_name_pos (char const*,int /*<<< orphan*/ ) ; 
 scalar_t__ chmod_cache_entry (struct cache_entry*,char) ; 
 int /*<<< orphan*/  die (char*,char,char const*) ; 
 int /*<<< orphan*/  report (char*,char,char const*) ; 
 int /*<<< orphan*/  strlen (char const*) ; 

__attribute__((used)) static void chmod_path(char flip, const char *path)
{
	int pos;
	struct cache_entry *ce;

	pos = cache_name_pos(path, strlen(path));
	if (pos < 0)
		goto fail;
	ce = active_cache[pos];
	if (chmod_cache_entry(ce, flip) < 0)
		goto fail;

	report("chmod %cx '%s'", flip, path);
	return;
 fail:
	die("git update-index: cannot chmod %cx '%s'", flip, path);
}