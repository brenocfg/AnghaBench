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
typedef  int /*<<< orphan*/  git_buf ;
typedef  char DIR ;

/* Variables and functions */
 int /*<<< orphan*/  GIT_BUF_INIT ; 
 int /*<<< orphan*/  cl_assert (char*) ; 
 int /*<<< orphan*/  closedir (char*) ; 
 int /*<<< orphan*/  git__free (char*) ; 
 char* git_buf_detach (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_buf_dispose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_buf_join (int /*<<< orphan*/ *,char,char*,int /*<<< orphan*/ ) ; 
 char* git_path_basename (char const*) ; 
 char* git_path_dirname (char const*) ; 
 char* opendir (char*) ; 
 struct dirent* readdir (char*) ; 
 scalar_t__ strcasecmp (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static char *get_filename(const char *in)
{
	char *search_dirname, *search_filename, *filename = NULL;
	git_buf out = GIT_BUF_INIT;
	DIR *dir;
	struct dirent *de;

	cl_assert(search_dirname = git_path_dirname(in));
	cl_assert(search_filename = git_path_basename(in));

	cl_assert(dir = opendir(search_dirname));

	while ((de = readdir(dir))) {
		if (strcasecmp(de->d_name, search_filename) == 0) {
			git_buf_join(&out, '/', search_dirname, de->d_name);
			filename = git_buf_detach(&out);
			break;
		}
	}

	closedir(dir);

	git__free(search_dirname);
	git__free(search_filename);
	git_buf_dispose(&out);

	return filename;
}