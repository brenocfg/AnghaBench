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
typedef  scalar_t__ time_t ;
struct stat {scalar_t__ st_uid; int /*<<< orphan*/  st_mode; } ;
struct dirent {char* d_name; } ;
typedef  int /*<<< orphan*/  namepath ;
typedef  int /*<<< orphan*/  DIR ;

/* Variables and functions */
 int /*<<< orphan*/  GSSD_CREDENTIAL_CACHE_FILE ; 
 int /*<<< orphan*/  PATH_MAX ; 
 scalar_t__ S_ISREG (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ccfile_substring ; 
 int /*<<< orphan*/  closedir (int /*<<< orphan*/ *) ; 
 scalar_t__ hostbased_initiator_cred ; 
 scalar_t__ is_a_valid_tgt_cache (char*,scalar_t__,int*,scalar_t__*) ; 
 scalar_t__ lstat (char*,struct stat*) ; 
 int /*<<< orphan*/ * opendir (char const*) ; 
 struct dirent* readdir (int /*<<< orphan*/ *) ; 
 int snprintf (char*,int,char*,char const*,char*) ; 
 scalar_t__ strcmp (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strcpy (char*,char*) ; 
 int /*<<< orphan*/ * strstr (char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
find_ccache_file(const char *dirpath, uid_t uid, char *rpath)
{
	DIR *dirp;
	struct dirent *dp;
	struct stat sb;
	time_t exptime, oexptime;
	int gotone, len, rating, orating;
	char namepath[PATH_MAX + 5 + 1];
	char retpath[PATH_MAX + 5 + 1];

	dirp = opendir(dirpath);
	if (dirp == NULL)
		return (0);
	gotone = 0;
	orating = 0;
	oexptime = 0;
	while ((dp = readdir(dirp)) != NULL) {
		len = snprintf(namepath, sizeof(namepath), "%s/%s", dirpath,
		    dp->d_name);
		if (len < sizeof(namepath) &&
		    (hostbased_initiator_cred == 0 || strcmp(namepath,
		     GSSD_CREDENTIAL_CACHE_FILE) != 0) &&
		    strstr(dp->d_name, ccfile_substring) != NULL &&
		    lstat(namepath, &sb) >= 0 &&
		    sb.st_uid == uid &&
		    S_ISREG(sb.st_mode)) {
			len = snprintf(namepath, sizeof(namepath), "FILE:%s/%s",
			    dirpath, dp->d_name);
			if (len < sizeof(namepath) &&
			    is_a_valid_tgt_cache(namepath, uid, &rating,
			    &exptime) != 0) {
				if (gotone == 0 || rating > orating ||
				    (rating == orating && exptime > oexptime)) {
					orating = rating;
					oexptime = exptime;
					strcpy(retpath, namepath);
					gotone = 1;
				}
			}
		}
	}
	closedir(dirp);
	if (gotone != 0) {
		strcpy(rpath, retpath);
		return (1);
	}
	return (0);
}