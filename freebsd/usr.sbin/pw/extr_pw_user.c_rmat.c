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
typedef  scalar_t__ uid_t ;
typedef  int /*<<< orphan*/  tmp ;
struct stat {scalar_t__ st_uid; int /*<<< orphan*/  st_mode; } ;
struct dirent {char* d_name; } ;
typedef  int /*<<< orphan*/  DIR ;

/* Variables and functions */
 int MAXPATHLEN ; 
 int /*<<< orphan*/  S_ISDIR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  closedir (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * opendir (char*) ; 
 struct dirent* readdir (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char*) ; 
 scalar_t__ stat (char*,struct stat*) ; 
 scalar_t__ strncmp (char*,char*,int) ; 
 int /*<<< orphan*/  system (char*) ; 

__attribute__((used)) static void
rmat(uid_t uid)
{
	DIR            *d = opendir("/var/at/jobs");

	if (d != NULL) {
		struct dirent  *e;

		while ((e = readdir(d)) != NULL) {
			struct stat     st;

			if (strncmp(e->d_name, ".lock", 5) != 0 &&
			    stat(e->d_name, &st) == 0 &&
			    !S_ISDIR(st.st_mode) &&
			    st.st_uid == uid) {
				char            tmp[MAXPATHLEN];

				snprintf(tmp, sizeof(tmp), "/usr/bin/atrm %s",
				    e->d_name);
				system(tmp);
			}
		}
		closedir(d);
	}
}