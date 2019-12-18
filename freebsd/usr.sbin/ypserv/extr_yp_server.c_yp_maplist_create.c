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
typedef  int /*<<< orphan*/  yp_mapname ;
typedef  int /*<<< orphan*/  yp_mapdir ;
struct ypmaplist {int /*<<< orphan*/ * map; struct ypmaplist* next; } ;
struct stat {int /*<<< orphan*/  st_mode; } ;
struct dirent {char const* d_name; } ;
typedef  int /*<<< orphan*/  DIR ;

/* Variables and functions */
 int /*<<< orphan*/  MAXPATHLEN ; 
 int /*<<< orphan*/  S_ISREG (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  closedir (int /*<<< orphan*/ *) ; 
 scalar_t__ debug ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  free (struct ypmaplist*) ; 
 scalar_t__ malloc (int) ; 
 int /*<<< orphan*/ * opendir (char*) ; 
 struct dirent* readdir (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char*,char const*) ; 
 scalar_t__ stat (char*,struct stat*) ; 
 scalar_t__ strcmp (char const*,char*) ; 
 int /*<<< orphan*/ * strdup (char*) ; 
 int /*<<< orphan*/ * strerror (int /*<<< orphan*/ ) ; 
 char* yp_dir ; 
 int /*<<< orphan*/  yp_error (char*,...) ; 
 int /*<<< orphan*/  yp_maplist_free (struct ypmaplist*) ; 

__attribute__((used)) static struct ypmaplist *
yp_maplist_create(const char *domain)
{
	char yp_mapdir[MAXPATHLEN + 2];
	char yp_mapname[MAXPATHLEN + 2];
	struct ypmaplist *cur = NULL;
	struct ypmaplist *yp_maplist = NULL;
	DIR *dird;
	struct dirent *dirp;
	struct stat statbuf;

	snprintf(yp_mapdir, sizeof(yp_mapdir), "%s/%s", yp_dir, domain);

	if ((dird = opendir(yp_mapdir)) == NULL) {
		yp_error("opendir(%s) failed: %s", yp_mapdir, strerror(errno));
		return(NULL);
	}

	while ((dirp = readdir(dird)) != NULL) {
		if (strcmp(dirp->d_name, ".") && strcmp(dirp->d_name, "..")) {
			snprintf(yp_mapname, sizeof(yp_mapname), "%s/%s",
							yp_mapdir,dirp->d_name);
			if (stat(yp_mapname, &statbuf) < 0 ||
						!S_ISREG(statbuf.st_mode))
				continue;
			if ((cur = (struct ypmaplist *)
				malloc(sizeof(struct ypmaplist))) == NULL) {
				yp_error("malloc() failed");
				closedir(dird);
				yp_maplist_free(yp_maplist);
				return(NULL);
			}
			if ((cur->map = strdup(dirp->d_name)) == NULL) {
				yp_error("strdup() failed: %s",strerror(errno));
				closedir(dird);
				yp_maplist_free(yp_maplist);
				free(cur);
				return(NULL);
			}
			cur->next = yp_maplist;
			yp_maplist = cur;
			if (debug)
				yp_error("map: %s", yp_maplist->map);
		}

	}
	closedir(dird);
	return(yp_maplist);
}