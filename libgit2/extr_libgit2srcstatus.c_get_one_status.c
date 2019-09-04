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
struct status_file_info {int count; unsigned int status; int fnm_flags; char const* expected; int ambiguous; } ;

/* Variables and functions */
 int FNM_CASEFOLD ; 
 int GIT_EAMBIGUOUS ; 
 int git__strcasecmp (char const*,char const*) ; 
 int git__strcmp (char const*,char const*) ; 
 scalar_t__ p_fnmatch (char const*,char const*,int) ; 

__attribute__((used)) static int get_one_status(const char *path, unsigned int status, void *data)
{
	struct status_file_info *sfi = data;
	int (*strcomp)(const char *a, const char *b);

	sfi->count++;
	sfi->status = status;

	strcomp = (sfi->fnm_flags & FNM_CASEFOLD) ? git__strcasecmp : git__strcmp;

	if (sfi->count > 1 ||
		(strcomp(sfi->expected, path) != 0 &&
		 p_fnmatch(sfi->expected, path, sfi->fnm_flags) != 0))
	{
		sfi->ambiguous = true;
		return GIT_EAMBIGUOUS; /* git_error_set will be done by caller */
	}

	return 0;
}