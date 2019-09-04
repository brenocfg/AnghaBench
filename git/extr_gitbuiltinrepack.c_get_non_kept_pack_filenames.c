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
struct string_list {int nr; TYPE_1__* items; } ;
struct dirent {int /*<<< orphan*/  d_name; } ;
struct TYPE_2__ {int /*<<< orphan*/  string; } ;
typedef  int /*<<< orphan*/  DIR ;

/* Variables and functions */
 int /*<<< orphan*/  closedir (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  file_exists (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  fspathcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mkpath (char*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/ * opendir (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  packdir ; 
 struct dirent* readdir (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  string_list_append_nodup (struct string_list*,char*) ; 
 int /*<<< orphan*/  strip_suffix (int /*<<< orphan*/ ,char*,size_t*) ; 
 char* xmemdupz (int /*<<< orphan*/ ,size_t) ; 

__attribute__((used)) static void get_non_kept_pack_filenames(struct string_list *fname_list,
					const struct string_list *extra_keep)
{
	DIR *dir;
	struct dirent *e;
	char *fname;

	if (!(dir = opendir(packdir)))
		return;

	while ((e = readdir(dir)) != NULL) {
		size_t len;
		int i;

		for (i = 0; i < extra_keep->nr; i++)
			if (!fspathcmp(e->d_name, extra_keep->items[i].string))
				break;
		if (extra_keep->nr > 0 && i < extra_keep->nr)
			continue;

		if (!strip_suffix(e->d_name, ".pack", &len))
			continue;

		fname = xmemdupz(e->d_name, len);

		if (!file_exists(mkpath("%s/%s.keep", packdir, fname)))
			string_list_append_nodup(fname_list, fname);
		else
			free(fname);
	}
	closedir(dir);
}