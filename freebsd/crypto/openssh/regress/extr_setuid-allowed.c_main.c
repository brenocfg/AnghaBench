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
struct statvfs {int f_flag; } ;

/* Variables and functions */
 scalar_t__ ENOSYS ; 
 int ST_NOSUID ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char const*,char*) ; 
 scalar_t__ statvfs (char const*,struct statvfs*) ; 
 int /*<<< orphan*/  stderr ; 
 char* strerror (scalar_t__) ; 
 int /*<<< orphan*/  usage () ; 

int
main(int argc, char **argv)
{
	const char *path = ".";
	struct statvfs sb;

	if (argc > 2)
		usage();
	else if (argc == 2)
		path = argv[1];

	if (statvfs(path, &sb) != 0) {
		/* Don't return an error if the host doesn't support statvfs */
		if (errno == ENOSYS)
			return 0;
		fprintf(stderr, "statvfs for \"%s\" failed: %s\n",
		     path, strerror(errno));
	}
	return (sb.f_flag & ST_NOSUID) ? 1 : 0;
}