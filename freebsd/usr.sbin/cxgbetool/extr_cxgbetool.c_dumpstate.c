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
struct t4_cudbg_dump {int len; int /*<<< orphan*/ * data; int /*<<< orphan*/  bitmap; scalar_t__ wr_flash; int /*<<< orphan*/  member_0; } ;

/* Variables and functions */
 int /*<<< orphan*/  CHELSIO_T4_CUDBG_DUMP ; 
 int EINVAL ; 
 int ENOMEM ; 
 int O_CREAT ; 
 int O_EXCL ; 
 int O_TRUNC ; 
 int O_WRONLY ; 
 int S_IRGRP ; 
 int S_IROTH ; 
 int S_IRUSR ; 
 int /*<<< orphan*/  close (int) ; 
 int doit (int /*<<< orphan*/ ,struct t4_cudbg_dump*) ; 
 int errno ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * malloc (int) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int,int) ; 
 int open (char const*,int,int) ; 
 int /*<<< orphan*/  warn (char*,char const*) ; 
 int /*<<< orphan*/  warnx (char*) ; 
 int /*<<< orphan*/  write (int,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int
dumpstate(int argc, const char *argv[])
{
	int rc, fd;
	struct t4_cudbg_dump dump = {0};
	const char *fname = argv[0];

	if (argc != 1) {
		warnx("dumpstate: incorrect number of arguments.");
		return (EINVAL);
	}

	dump.wr_flash = 0;
	memset(&dump.bitmap, 0xff, sizeof(dump.bitmap));
	dump.len = 8 * 1024 * 1024;
	dump.data = malloc(dump.len);
	if (dump.data == NULL) {
		return (ENOMEM);
	}

	rc = doit(CHELSIO_T4_CUDBG_DUMP, &dump);
	if (rc != 0)
		goto done;

	fd = open(fname, O_CREAT | O_TRUNC | O_EXCL | O_WRONLY,
	    S_IRUSR | S_IRGRP | S_IROTH);
	if (fd < 0) {
		warn("open(%s)", fname);
		rc = errno;
		goto done;
	}
	write(fd, dump.data, dump.len);
	close(fd);
done:
	free(dump.data);
	return (rc);
}