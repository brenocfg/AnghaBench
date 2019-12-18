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
typedef  char uint64_t ;
typedef  int /*<<< orphan*/  trail_size ;
struct stat {char st_size; int /*<<< orphan*/  st_mode; } ;
struct TYPE_2__ {char* adh_trail_name; int /*<<< orphan*/  adh_remote; int /*<<< orphan*/  adh_directory; int /*<<< orphan*/  adh_trail_dirfd; int /*<<< orphan*/ * adh_trail_dirfp; } ;

/* Variables and functions */
 int /*<<< orphan*/  AT_SYMLINK_NOFOLLOW ; 
 int /*<<< orphan*/  EX_CONFIG ; 
 int /*<<< orphan*/  EX_TEMPFAIL ; 
 int /*<<< orphan*/  PJDLOG_ASSERT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  S_ISREG (int /*<<< orphan*/ ) ; 
 TYPE_1__* adhost ; 
 int fstatat (int /*<<< orphan*/ ,char*,struct stat*,int /*<<< orphan*/ ) ; 
 char htole64 (char) ; 
 int /*<<< orphan*/  pjdlog_exit (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  pjdlog_exitx (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,char*) ; 
 int proto_send (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  trail_last (int /*<<< orphan*/ *,char*,int) ; 

__attribute__((used)) static void
receiver_connect(void)
{
	uint64_t trail_size;
	struct stat sb;

	PJDLOG_ASSERT(adhost->adh_trail_dirfp != NULL);

	trail_last(adhost->adh_trail_dirfp, adhost->adh_trail_name,
	    sizeof(adhost->adh_trail_name));

	if (adhost->adh_trail_name[0] == '\0') {
		trail_size = 0;
	} else {
		if (fstatat(adhost->adh_trail_dirfd, adhost->adh_trail_name,
		    &sb, AT_SYMLINK_NOFOLLOW) == -1) {
			pjdlog_exit(EX_CONFIG, "Unable to stat \"%s/%s\"",
			    adhost->adh_directory, adhost->adh_trail_name);
		}
		if (!S_ISREG(sb.st_mode)) {
			pjdlog_exitx(EX_CONFIG,
			    "File \"%s/%s\" is not a regular file.",
			    adhost->adh_directory, adhost->adh_trail_name);
		}
		trail_size = sb.st_size;
	}
	trail_size = htole64(trail_size);
	if (proto_send(adhost->adh_remote, &trail_size,
	    sizeof(trail_size)) == -1) {
		pjdlog_exit(EX_TEMPFAIL,
		    "Unable to send size of the most recent trail file");
	}
	if (proto_send(adhost->adh_remote, adhost->adh_trail_name,
	    sizeof(adhost->adh_trail_name)) == -1) {
		pjdlog_exit(EX_TEMPFAIL,
		    "Unable to send name of the most recent trail file");
	}
}