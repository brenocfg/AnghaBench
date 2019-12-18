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
struct TYPE_2__ {scalar_t__ (* check ) (int,char const*) ;char* name; int (* hide ) (int,char const*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  O_RDWR ; 
 int /*<<< orphan*/  SEEK_SET ; 
 int /*<<< orphan*/  close (int) ; 
 TYPE_1__* exec_formats ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char const*,...) ; 
 scalar_t__ lseek (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int open (char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  perror (char const*) ; 
 int /*<<< orphan*/  stderr ; 
 scalar_t__ stub1 (int,char const*) ; 
 int stub2 (int,char const*) ; 
 scalar_t__ verbose ; 

int
hide_syms(const char *filename)
{
	int fd, i, n, rv;

	fd = open(filename, O_RDWR, 0);
	if (fd == -1) {
		perror(filename);
		return 1;
	}

	rv = 0;

        n = sizeof exec_formats / sizeof exec_formats[0];
        for (i = 0; i < n; i++) {
		if (lseek(fd, 0, SEEK_SET) != 0) {
			perror(filename);
			goto err;
		}
                if ((*exec_formats[i].check)(fd, filename) != 0)
                        break;
	}
	if (i == n) {
		fprintf(stderr, "%s: unknown executable format\n", filename);
		goto err;
	}

	if (verbose)
		fprintf(stderr, "%s is an %s binary\n", filename,
		    exec_formats[i].name);

	if (lseek(fd, 0, SEEK_SET) != 0) {
		perror(filename);
		goto err;
	}
	rv = (*exec_formats[i].hide)(fd, filename);

out:
	close (fd);
	return (rv);

err:
	rv = 1;
	goto out;
}