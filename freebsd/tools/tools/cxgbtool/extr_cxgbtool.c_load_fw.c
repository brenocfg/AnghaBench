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
struct ch_mem_range {int len; int /*<<< orphan*/  buf; } ;
typedef  int /*<<< orphan*/  op ;

/* Variables and functions */
 int /*<<< orphan*/  CHELSIO_LOAD_FW ; 
 int MAX_FW_IMAGE_SIZE ; 
 int /*<<< orphan*/  O_RDONLY ; 
 int /*<<< orphan*/  bzero (struct ch_mem_range*,int) ; 
 int /*<<< orphan*/  close (int) ; 
 scalar_t__ doit (char const*,int /*<<< orphan*/ ,struct ch_mem_range*) ; 
 int /*<<< orphan*/  err (int,char*) ; 
 int /*<<< orphan*/  errx (int,char*) ; 
 int /*<<< orphan*/  malloc (int) ; 
 int open (char const*,int /*<<< orphan*/ ) ; 
 int read (int,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int
load_fw(int argc, char *argv[], int start_arg, const char *iff_name)
{
	int fd, len;
	struct ch_mem_range op;
	const char *fname = argv[start_arg];

	if (argc != start_arg + 1) return -1;

	fd = open(fname, O_RDONLY);
	if (fd < 0)
		err(1, "load firmware");

	bzero(&op, sizeof(op));
	op.buf = malloc(MAX_FW_IMAGE_SIZE + 1);
	if (!op.buf)
		err(1, "load firmware");

	len = read(fd, op.buf, MAX_FW_IMAGE_SIZE + 1);
	if (len < 0)
		err(1, "load firmware");
 	if (len > MAX_FW_IMAGE_SIZE)
		errx(1, "FW image too large");

	op.len = len;
	if (doit(iff_name, CHELSIO_LOAD_FW, &op) < 0)
		err(1, "load firmware");

	close(fd);
	return 0;
}