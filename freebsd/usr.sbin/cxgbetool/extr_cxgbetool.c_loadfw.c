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
struct t4_data {scalar_t__ data; int /*<<< orphan*/  len; int /*<<< orphan*/  member_0; } ;
struct stat {int /*<<< orphan*/  st_size; int /*<<< orphan*/  member_0; } ;

/* Variables and functions */
 int /*<<< orphan*/  CHELSIO_T4_LOAD_FW ; 
 int EINVAL ; 
 scalar_t__ MAP_FAILED ; 
 int /*<<< orphan*/  MAP_PRIVATE ; 
 int /*<<< orphan*/  O_RDONLY ; 
 int /*<<< orphan*/  PROT_READ ; 
 int /*<<< orphan*/  close (int) ; 
 int doit (int /*<<< orphan*/ ,struct t4_data*) ; 
 int errno ; 
 scalar_t__ fstat (int,struct stat*) ; 
 scalar_t__ mmap (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  munmap (scalar_t__,int /*<<< orphan*/ ) ; 
 int open (char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  warn (char*,...) ; 
 int /*<<< orphan*/  warnx (char*) ; 

__attribute__((used)) static int
loadfw(int argc, const char *argv[])
{
	int rc, fd;
	struct t4_data data = {0};
	const char *fname = argv[0];
	struct stat st = {0};

	if (argc != 1) {
		warnx("loadfw: incorrect number of arguments.");
		return (EINVAL);
	}

	fd = open(fname, O_RDONLY);
	if (fd < 0) {
		warn("open(%s)", fname);
		return (errno);
	}

	if (fstat(fd, &st) < 0) {
		warn("fstat");
		close(fd);
		return (errno);
	}

	data.len = st.st_size;
	data.data = mmap(0, data.len, PROT_READ, MAP_PRIVATE, fd, 0);
	if (data.data == MAP_FAILED) {
		warn("mmap");
		close(fd);
		return (errno);
	}

	rc = doit(CHELSIO_T4_LOAD_FW, &data);
	munmap(data.data, data.len);
	close(fd);
	return (rc);
}