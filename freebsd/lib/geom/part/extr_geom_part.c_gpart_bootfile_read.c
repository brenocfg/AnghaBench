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
struct stat {scalar_t__ st_size; int /*<<< orphan*/  st_mode; } ;
typedef  scalar_t__ ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  EXIT_FAILURE ; 
 int /*<<< orphan*/  O_RDONLY ; 
 int /*<<< orphan*/  S_ISREG (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  err (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  errx (int /*<<< orphan*/ ,char*,char const*,...) ; 
 void* malloc (scalar_t__) ; 
 int open (char const*,int /*<<< orphan*/ ) ; 
 scalar_t__ read (int,void*,scalar_t__) ; 
 int stat (char const*,struct stat*) ; 

__attribute__((used)) static void *
gpart_bootfile_read(const char *bootfile, ssize_t *size)
{
	struct stat sb;
	void *code;
	int fd;

	if (stat(bootfile, &sb) == -1)
		err(EXIT_FAILURE, "%s", bootfile);
	if (!S_ISREG(sb.st_mode))
		errx(EXIT_FAILURE, "%s: not a regular file", bootfile);
	if (sb.st_size == 0)
		errx(EXIT_FAILURE, "%s: empty file", bootfile);
	if (*size > 0 && sb.st_size > *size)
		errx(EXIT_FAILURE, "%s: file too big (%zu limit)", bootfile,
		    *size);

	*size = sb.st_size;

	fd = open(bootfile, O_RDONLY);
	if (fd == -1)
		err(EXIT_FAILURE, "%s", bootfile);
	code = malloc(*size);
	if (code == NULL)
		err(EXIT_FAILURE, NULL);
	if (read(fd, code, *size) != *size)
		err(EXIT_FAILURE, "%s", bootfile);
	close(fd);

	return (code);
}