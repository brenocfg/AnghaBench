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
struct dirent {char* d_name; } ;
typedef  int /*<<< orphan*/  DIR ;

/* Variables and functions */
 int MAXDEWEY ; 
 int /*<<< orphan*/  MAXNAMLEN ; 
 int /*<<< orphan*/  bcopy (int*,int*,int) ; 
 int /*<<< orphan*/  closedir (int /*<<< orphan*/ *) ; 
 scalar_t__ cmpndewey (int*,int,int*,int) ; 
 char* concat (char*,char*,char*) ; 
 int getdewey (int*,char*) ; 
 int /*<<< orphan*/ * opendir (char*) ; 
 struct dirent* readdir (int /*<<< orphan*/ *) ; 
 scalar_t__ strcmp (char*,char*) ; 
 int /*<<< orphan*/  strcpy (char*,char*) ; 
 int strlen (char*) ; 
 scalar_t__ strncmp (char*,char*,int) ; 

char *
search_lib_dir(char *dir, char *name, int *majorp, int *minorp, int do_dot_a)
{
	size_t		namelen;
	DIR		*dd;
	struct dirent	*dp;
	int		best_dewey[MAXDEWEY];
	int		best_ndewey;
	char		dot_a_name[MAXNAMLEN+1];
	char		dot_so_name[MAXNAMLEN+1];

	if((dd = opendir(dir)) == NULL)
		return NULL;

	namelen = strlen(name);
	best_ndewey = 0;
	dot_a_name[0] = '\0';
	dot_so_name[0] = '\0';

	while((dp = readdir(dd)) != NULL) {
		char *extension;

		if(strlen(dp->d_name) < 3 + namelen + 2 ||	/* lib+xxx+.a */
		   strncmp(dp->d_name, "lib", 3) != 0 ||
		   strncmp(dp->d_name + 3, name, namelen) != 0 ||
		   dp->d_name[3+namelen] != '.')
			continue;

		extension = dp->d_name + 3 + namelen + 1;	/* a or so.* */

		if(strncmp(extension, "so.", 3) == 0) {
			int cur_dewey[MAXDEWEY];
			int cur_ndewey;

			cur_ndewey = getdewey(cur_dewey, extension+3);
			if(cur_ndewey < 2)	/* Too few version numbers */
				continue;

			if(*majorp != -1) {	/* Need exact match on major */
				if(cur_dewey[0] != *majorp)
					continue;
				if(*minorp != -1) {  /* Need minor >= minimum */
					if(cur_dewey[1] < *minorp)
						continue;
				}
			}

			if(cmpndewey(cur_dewey, cur_ndewey, best_dewey,
			   best_ndewey) <= 0)	/* No better than prior match */
				continue;

			/* We found a better match */
			strcpy(dot_so_name, dp->d_name);
			bcopy(cur_dewey, best_dewey,
				cur_ndewey * sizeof best_dewey[0]);
			best_ndewey = cur_ndewey;
		} else if(do_dot_a && strcmp(extension, "a") == 0)
			strcpy(dot_a_name, dp->d_name);
	}
	closedir(dd);

	if(dot_so_name[0] != '\0') {
		*majorp = best_dewey[0];
		*minorp = best_dewey[1];
		return concat(dir, "/", dot_so_name);
	}

	if(dot_a_name[0] != '\0')
		return concat(dir, "/", dot_a_name);

	return NULL;
}