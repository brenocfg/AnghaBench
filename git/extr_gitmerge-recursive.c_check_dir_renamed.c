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
struct hashmap {int dummy; } ;
struct dir_rename_entry {int dummy; } ;

/* Variables and functions */
 struct dir_rename_entry* dir_rename_find_entry (struct hashmap*,char*) ; 
 int /*<<< orphan*/  free (char*) ; 
 char* strrchr (char*,char) ; 
 char* xstrdup (char const*) ; 

__attribute__((used)) static struct dir_rename_entry *check_dir_renamed(const char *path,
						  struct hashmap *dir_renames)
{
	char *temp = xstrdup(path);
	char *end;
	struct dir_rename_entry *entry = NULL;

	while ((end = strrchr(temp, '/'))) {
		*end = '\0';
		entry = dir_rename_find_entry(dir_renames, temp);
		if (entry)
			break;
	}
	free(temp);
	return entry;
}