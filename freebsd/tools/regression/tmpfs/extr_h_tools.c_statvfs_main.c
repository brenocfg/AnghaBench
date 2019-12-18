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
typedef  int /*<<< orphan*/  uintmax_t ;
struct statfs {scalar_t__ f_files; scalar_t__ f_bfree; scalar_t__ f_blocks; scalar_t__ f_bsize; int /*<<< orphan*/  f_version; } ;
typedef  int /*<<< orphan*/  buf ;

/* Variables and functions */
 int EXIT_FAILURE ; 
 int EXIT_SUCCESS ; 
 int /*<<< orphan*/  STATFS_VERSION ; 
 int /*<<< orphan*/  memset (struct statfs*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  perror (char*) ; 
 int /*<<< orphan*/  printf (char*,int /*<<< orphan*/ ) ; 
 int statfs (char*,struct statfs*) ; 

int
statvfs_main(int argc, char **argv)
{
	int error;
	struct statfs buf;

	if (argc < 2)
		return EXIT_FAILURE;

	memset(&buf, 0, sizeof(buf));
	buf.f_version = STATFS_VERSION;
	error = statfs(argv[1], &buf);
	if (error != 0) {
		perror("statvfs");
		return EXIT_FAILURE;
	}

	(void)printf("f_bsize=%ju\n", (uintmax_t)buf.f_bsize);
	(void)printf("f_blocks=%ju\n", (uintmax_t)buf.f_blocks);
	(void)printf("f_bfree=%ju\n", (uintmax_t)buf.f_bfree);
	(void)printf("f_files=%ju\n", (uintmax_t)buf.f_files);

	return EXIT_SUCCESS;
}