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
struct dirent {int /*<<< orphan*/  d_name; } ;
typedef  int /*<<< orphan*/  FILE ;
typedef  int /*<<< orphan*/  DIR ;

/* Variables and functions */
 int /*<<< orphan*/  LOG_ERR ; 
 int LS_DIR_FLAG ; 
 int asprintf (char**,char*,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  closedir (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free_files (char**,int) ; 
 scalar_t__ hide_file (int /*<<< orphan*/ ,int) ; 
 int list_files (int /*<<< orphan*/ *,char const**,int,int) ; 
 int /*<<< orphan*/ * opendir (char const*) ; 
 struct dirent* readdir (int /*<<< orphan*/ *) ; 
 void* realloc (char**,int) ; 
 int /*<<< orphan*/  syslog (int /*<<< orphan*/ ,char*,char const*) ; 

__attribute__((used)) static int
list_dir(FILE *out, const char *directory, int flags)
{
    DIR *d = opendir(directory);
    struct dirent *ent;
    char **files = NULL;
    int n_files = 0;
    int ret;

    if(d == NULL) {
	syslog(LOG_ERR, "%s: %m", directory);
	return -1;
    }
    while((ent = readdir(d)) != NULL) {
	void *tmp;

	if(hide_file(ent->d_name, flags))
	    continue;
	tmp = realloc(files, (n_files + 1) * sizeof(*files));
	if (tmp == NULL) {
	    syslog(LOG_ERR, "%s: out of memory", directory);
	    free_files (files, n_files);
	    closedir (d);
	    return -1;
	}
	files = tmp;
	ret = asprintf(&files[n_files], "%s/%s", directory, ent->d_name);
	if (ret == -1) {
	    syslog(LOG_ERR, "%s: out of memory", directory);
	    free_files (files, n_files);
	    closedir (d);
	    return -1;
	}
	++n_files;
    }
    closedir(d);
    return list_files(out, (const char**)files, n_files, flags | LS_DIR_FLAG);
}