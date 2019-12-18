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
typedef  char uint8_t ;
typedef  int uint32_t ;
typedef  scalar_t__ ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  MAXPATHLEN ; 
 int NVME_MAX_XFER_SIZE ; 
 int O_CREAT ; 
 int O_TRUNC ; 
 int O_WRONLY ; 
 int /*<<< orphan*/  PAGE_SIZE ; 
 char* aligned_alloc (int /*<<< orphan*/ ,int) ; 
 int be32dec (char*) ; 
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  err (int,char*,...) ; 
 int /*<<< orphan*/  errx (int,char*,...) ; 
 int /*<<< orphan*/  free (char*) ; 
 scalar_t__ memcmp (char*,char*,int) ; 
 int open (char*,int,int) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int /*<<< orphan*/  wdc_append_serial_name (int,char*,int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  wdc_get_data (int,int,size_t,int,int,char*,size_t) ; 
 scalar_t__ write (int,char*,size_t) ; 

__attribute__((used)) static void
wdc_do_dump(int fd, char *tmpl, const char *suffix, uint32_t opcode,
    uint32_t cmd, int len_off)
{
	int first;
	int fd2;
	uint8_t *buf;
	uint32_t len, offset;
	size_t resid;

	wdc_append_serial_name(fd, tmpl, MAXPATHLEN, suffix);

	/* XXX overwrite protection? */
	fd2 = open(tmpl, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd2 < 0)
		err(1, "open %s", tmpl);
	buf = aligned_alloc(PAGE_SIZE, NVME_MAX_XFER_SIZE);
	if (buf == NULL)
		errx(1, "Can't get buffer to read dump");
	offset = 0;
	len = NVME_MAX_XFER_SIZE;
	first = 1;

	do {
		resid = len > NVME_MAX_XFER_SIZE ? NVME_MAX_XFER_SIZE : len;
		wdc_get_data(fd, opcode, resid, offset, cmd, buf, resid);

		if (first) {
			len = be32dec(buf + len_off);
			if (len == 0)
				errx(1, "No data for %s", suffix);
			if (memcmp("E6LG", buf, 4) != 0)
				printf("Expected header of E6LG, found '%4.4s' instead\n",
				    buf);
			printf("Dumping %d bytes of version %d.%d log to %s\n", len,
			    buf[8], buf[9], tmpl);
			/*
			 * Adjust amount to dump if total dump < 1MB,
			 * though it likely doesn't matter to the WDC
			 * analysis tools.
			 */
			if (resid > len)
				resid = len;
			first = 0;
		}
		if (write(fd2, buf, resid) != (ssize_t)resid)
			err(1, "write");
		offset += resid;
		len -= resid;
	} while (len > 0);
	free(buf);
	close(fd2);
}