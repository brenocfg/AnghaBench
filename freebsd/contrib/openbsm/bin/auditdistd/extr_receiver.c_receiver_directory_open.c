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
struct stat {int dummy; } ;
struct TYPE_2__ {int adh_trail_dirfd; int /*<<< orphan*/ * adh_trail_dirfp; int /*<<< orphan*/  adh_directory; } ;

/* Variables and functions */
 scalar_t__ ENOENT ; 
 int /*<<< orphan*/  EX_CONFIG ; 
 int O_DIRECTORY ; 
 int O_RDONLY ; 
 TYPE_1__* adhost ; 
 int dirfd (int /*<<< orphan*/ *) ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/ * fdopendir (int) ; 
 void* open (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/ * opendir (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pjdlog_exit (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  receiver_directory_create () ; 
 int stat (int /*<<< orphan*/ ,struct stat*) ; 

__attribute__((used)) static void
receiver_directory_open(void)
{

#ifdef HAVE_FDOPENDIR
	adhost->adh_trail_dirfd = open(adhost->adh_directory,
	    O_RDONLY | O_DIRECTORY);
	if (adhost->adh_trail_dirfd == -1) {
		if (errno == ENOENT) {
			receiver_directory_create();
			adhost->adh_trail_dirfd = open(adhost->adh_directory,
			    O_RDONLY | O_DIRECTORY);
		}
		if (adhost->adh_trail_dirfd == -1) {
			pjdlog_exit(EX_CONFIG,
			    "Unable to open directory \"%s\"",
			    adhost->adh_directory);
		}
	}
	adhost->adh_trail_dirfp = fdopendir(adhost->adh_trail_dirfd);
	if (adhost->adh_trail_dirfp == NULL) {
		pjdlog_exit(EX_CONFIG, "Unable to fdopen directory \"%s\"",
		    adhost->adh_directory);
	}
#else
	struct stat sb;

	if (stat(adhost->adh_directory, &sb) == -1) {
		if (errno == ENOENT) {
			receiver_directory_create();
		} else {
			pjdlog_exit(EX_CONFIG,
			    "Unable to stat directory \"%s\"",
			    adhost->adh_directory);
		}
	}
	adhost->adh_trail_dirfp = opendir(adhost->adh_directory);
	if (adhost->adh_trail_dirfp == NULL) {
		pjdlog_exit(EX_CONFIG, "Unable to open directory \"%s\"",
		    adhost->adh_directory);
	}
	adhost->adh_trail_dirfd = dirfd(adhost->adh_trail_dirfp);
#endif
}