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
struct group {scalar_t__ gr_gid; char** gr_mem; } ;
struct TYPE_2__ {scalar_t__ pw_gid; } ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int errno ; 
 int /*<<< orphan*/  fatalerror (char*) ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 char* fgetln (int /*<<< orphan*/ *,size_t*) ; 
 int /*<<< orphan*/ * fopen (char*,char*) ; 
 int /*<<< orphan*/  free (char*) ; 
 struct group* getgrnam (char*) ; 
 char* malloc (size_t) ; 
 int /*<<< orphan*/  memcpy (char*,char*,size_t) ; 
 TYPE_1__* pw ; 
 scalar_t__ strcmp (char*,char*) ; 
 char* strdup (char*) ; 
 int /*<<< orphan*/  strspn (char*,char*) ; 
 char* strtok (char*,char*) ; 

__attribute__((used)) static int
checkuser(char *fname, char *name, int pwset, char **residue, int *ecode)
{
	FILE *fd;
	int found = 0;
	size_t len;
	char *line, *mp, *p;

	if (ecode != NULL)
		*ecode = 0;
	if ((fd = fopen(fname, "r")) != NULL) {
		while (!found && (line = fgetln(fd, &len)) != NULL) {
			/* skip comments */
			if (line[0] == '#')
				continue;
			if (line[len - 1] == '\n') {
				line[len - 1] = '\0';
				mp = NULL;
			} else {
				if ((mp = malloc(len + 1)) == NULL)
					fatalerror("Ran out of memory.");
				memcpy(mp, line, len);
				mp[len] = '\0';
				line = mp;
			}
			/* avoid possible leading and trailing whitespace */
			p = strtok(line, " \t");
			/* skip empty lines */
			if (p == NULL)
				goto nextline;
			/*
			 * if first chr is '@', check group membership
			 */
			if (p[0] == '@') {
				int i = 0;
				struct group *grp;

				if (p[1] == '\0') /* single @ matches anyone */
					found = 1;
				else {
					if ((grp = getgrnam(p+1)) == NULL)
						goto nextline;
					/*
					 * Check user's default group
					 */
					if (pwset && grp->gr_gid == pw->pw_gid)
						found = 1;
					/*
					 * Check supplementary groups
					 */
					while (!found && grp->gr_mem[i])
						found = strcmp(name,
							grp->gr_mem[i++])
							== 0;
				}
			}
			/*
			 * Otherwise, just check for username match
			 */
			else
				found = strcmp(p, name) == 0;
			/*
			 * Save the rest of line to "residue" if matched
			 */
			if (found && residue) {
				if ((p = strtok(NULL, "")) != NULL)
					p += strspn(p, " \t");
				if (p && *p) {
				 	if ((*residue = strdup(p)) == NULL)
						fatalerror("Ran out of memory.");
				} else
					*residue = NULL;
			}
nextline:
			if (mp)
				free(mp);
		}
		(void) fclose(fd);
	} else if (ecode != NULL)
		*ecode = errno;
	return (found);
}