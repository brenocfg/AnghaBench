#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct dirent {char* d_name; } ;
typedef  int /*<<< orphan*/  pattern ;
typedef  int /*<<< orphan*/  path ;
struct TYPE_9__ {struct TYPE_9__* next; TYPE_2__* archives; int /*<<< orphan*/  lang; } ;
typedef  TYPE_1__ lmo_catalog_t ;
struct TYPE_10__ {struct TYPE_10__* next; } ;
typedef  TYPE_2__ lmo_archive_t ;
typedef  int /*<<< orphan*/  DIR ;

/* Variables and functions */
 int PATH_MAX ; 
 TYPE_1__* _lmo_active_catalog ; 
 TYPE_1__* _lmo_catalogs ; 
 int /*<<< orphan*/  closedir (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fnmatch (char*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (TYPE_1__*) ; 
 int /*<<< orphan*/  lmo_change_catalog (char const*) ; 
 TYPE_2__* lmo_open (char*) ; 
 TYPE_1__* malloc (int) ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/ * opendir (char const*) ; 
 struct dirent* readdir (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char const*,...) ; 

int lmo_load_catalog(const char *lang, const char *dir)
{
	DIR *dh = NULL;
	char pattern[16];
	char path[PATH_MAX];
	struct dirent *de = NULL;

	lmo_archive_t *ar = NULL;
	lmo_catalog_t *cat = NULL;

	if (!lmo_change_catalog(lang))
		return 0;

	if (!dir || !(dh = opendir(dir)))
		goto err;

	if (!(cat = malloc(sizeof(*cat))))
		goto err;

	memset(cat, 0, sizeof(*cat));

	snprintf(cat->lang, sizeof(cat->lang), "%s", lang);
	snprintf(pattern, sizeof(pattern), "*.%s.lmo", lang);

	while ((de = readdir(dh)) != NULL)
	{
		if (!fnmatch(pattern, de->d_name, 0))
		{
			snprintf(path, sizeof(path), "%s/%s", dir, de->d_name);
			ar = lmo_open(path);

			if (ar)
			{
				ar->next = cat->archives;
				cat->archives = ar;
			}
		}
	}

	closedir(dh);

	cat->next = _lmo_catalogs;
	_lmo_catalogs = cat;

	if (!_lmo_active_catalog)
		_lmo_active_catalog = cat;

	return 0;

err:
	if (dh) closedir(dh);
	if (cat) free(cat);

	return -1;
}