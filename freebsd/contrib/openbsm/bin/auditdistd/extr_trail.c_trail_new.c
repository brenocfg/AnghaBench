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
struct trail {int tr_filefd; int /*<<< orphan*/  tr_magic; int /*<<< orphan*/ * tr_dirfp; int /*<<< orphan*/  tr_dirname; } ;

/* Variables and functions */
 scalar_t__ ENAMETOOLONG ; 
 scalar_t__ ENOENT ; 
 int /*<<< orphan*/  LOG_ERR ; 
 int /*<<< orphan*/  TRAIL_MAGIC ; 
 struct trail* calloc (int,int) ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  free (struct trail*) ; 
 int mkdir (char const*,int) ; 
 void* opendir (char const*) ; 
 int /*<<< orphan*/  pjdlog_errno (int /*<<< orphan*/ ,char*,char const*) ; 
 int /*<<< orphan*/  pjdlog_error (char*,char const*) ; 
 int strlcpy (int /*<<< orphan*/ ,char const*,int) ; 

struct trail *
trail_new(const char *dirname, bool create)
{
	struct trail *trail;

	trail = calloc(1, sizeof(*trail));

	if (strlcpy(trail->tr_dirname, dirname, sizeof(trail->tr_dirname)) >=
	    sizeof(trail->tr_dirname)) {
		free(trail);
		pjdlog_error("Directory name too long (\"%s\").", dirname);
		errno = ENAMETOOLONG;
		return (NULL);
	}
	trail->tr_dirfp = opendir(dirname);
	if (trail->tr_dirfp == NULL) {
		if (create && errno == ENOENT) {
			if (mkdir(dirname, 0700) == -1) {
				pjdlog_errno(LOG_ERR,
				    "Unable to create directory \"%s\"",
				    dirname);
				free(trail);
				return (NULL);
			}
			/* TODO: Set directory ownership. */
		} else {
			pjdlog_errno(LOG_ERR,
			    "Unable to open directory \"%s\"",
			    dirname);
			free(trail);
			return (NULL);
		}
		trail->tr_dirfp = opendir(dirname);
		if (trail->tr_dirfp == NULL) {
			pjdlog_errno(LOG_ERR,
			    "Unable to open directory \"%s\"",
			    dirname);
			free(trail);
			return (NULL);
		}
	}
	trail->tr_filefd = -1;
	trail->tr_magic = TRAIL_MAGIC;
	return (trail);
}