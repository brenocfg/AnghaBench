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
typedef  int /*<<< orphan*/  buf ;

/* Variables and functions */
 int BCMFW_BSIZE ; 
 int BCMFW_BULK_EP ; 
 int BCMFW_INTR_EP ; 
 int /*<<< orphan*/  LOG_ERR ; 
 int /*<<< orphan*/  O_RDONLY ; 
 int /*<<< orphan*/  O_WRONLY ; 
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  errno ; 
 int open (char const*,int /*<<< orphan*/ ) ; 
 int read (int,char*,int) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char const*,int) ; 
 int /*<<< orphan*/  strerror (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  syslog (int /*<<< orphan*/ ,char*,char const*,char,...) ; 
 int /*<<< orphan*/  usleep (int) ; 
 int write (int,char*,int) ; 

__attribute__((used)) static int
bcmfw_load_firmware(char const *name, char const *md, char const *fw)
{
	char	buf[BCMFW_BSIZE];
	int	intr = -1, bulk = -1, fd = -1, error = -1, len;

	/* Open interrupt endpoint device */
	snprintf(buf, sizeof(buf), "/dev/%s.%d", name, BCMFW_INTR_EP);
	if ((intr = open(buf, O_RDONLY)) < 0) {
		syslog(LOG_ERR, "Could not open(%s). %s (%d)",
				buf, strerror(errno), errno);
		goto out;
	}

	/* Open bulk endpoint device */
	snprintf(buf, sizeof(buf), "/dev/%s.%d", name, BCMFW_BULK_EP);
	if ((bulk = open(buf, O_WRONLY)) < 0) {
		syslog(LOG_ERR, "Could not open(%s). %s (%d)",
				buf, strerror(errno), errno);
		goto out;
	}

	/* 
	 * Load mini-driver 
	 */

	if ((fd = open(md, O_RDONLY)) < 0) {
		syslog(LOG_ERR, "Could not open(%s). %s (%d)",
				md, strerror(errno), errno);
		goto out;
	}

	for (;;) {
		len = read(fd, buf, sizeof(buf));
		if (len < 0) {
			syslog(LOG_ERR, "Could not read(%s). %s (%d)",
					md, strerror(errno), errno);
			goto out;
		}
		if (len == 0)
			break;

		len = write(bulk, buf, len);
		if (len < 0) {
			syslog(LOG_ERR, "Could not write(/dev/%s.%d). %s (%d)",
					name, BCMFW_BULK_EP, strerror(errno),
					errno);
			goto out;
		}
	}

	close(fd);
	fd = -1;

	usleep(10);

	/* 
	 * Memory select 
	 */

	if (write(bulk, "#", 1) < 0) {
		syslog(LOG_ERR, "Could not write(/dev/%s.%d). %s (%d)",
				name, BCMFW_BULK_EP, strerror(errno), errno);
		goto out;
	}

	if (read(intr, buf, sizeof(buf)) < 0) {
		syslog(LOG_ERR, "Could not read(/dev/%s.%d). %s (%d)",
				name, BCMFW_INTR_EP, strerror(errno), errno);
		goto out;
	}

	if (buf[0] != '#') {
		syslog(LOG_ERR, "%s: Memory select failed (%c)", name, buf[0]);
		goto out;
	}

	/*
	 * Load firmware
	 */

	if ((fd = open(fw, O_RDONLY)) < 0) {
		syslog(LOG_ERR, "Could not open(%s). %s (%d)",
				fw, strerror(errno), errno);
		goto out;
	}

	for (;;) {
		len = read(fd, buf, sizeof(buf));
		if (len < 0) {
			syslog(LOG_ERR, "Could not read(%s). %s (%d)",
					fw, strerror(errno), errno);
			goto out;
		}
		if (len == 0)
			break;

		len = write(bulk, buf, len);
		if (len < 0) {
			syslog(LOG_ERR, "Could not write(/dev/%s.%d). %s (%d)",
					name, BCMFW_BULK_EP, strerror(errno),
					errno);
			goto out;
		}
	}

	close(fd);
	fd = -1;

	if (read(intr, buf, sizeof(buf)) < 0) {
		syslog(LOG_ERR, "Could not read(/dev/%s.%d). %s (%d)",
				name, BCMFW_INTR_EP, strerror(errno), errno);
		goto out;
	}

	if (buf[0] != '.') {
		syslog(LOG_ERR, "%s: Could not load firmware (%c)",
				name, buf[0]);
		goto out;
	}

	usleep(500000);
	error = 0;
out:
	if (fd != -1)
		close(fd);
	if (bulk != -1)
		close(bulk);
	if (intr != -1)
		close(intr);

	return (error);
}