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

/* Variables and functions */
 int EIO ; 
 int /*<<< orphan*/  LOG_ERR ; 
 int /*<<< orphan*/  SYS_HOSTNAME ; 
 int /*<<< orphan*/  memset (char*,int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  newline_to_null (char*) ; 
 scalar_t__ read (int,char*,size_t) ; 
 int /*<<< orphan*/  strip_domain (char*) ; 
 int /*<<< orphan*/  syslog (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int read_hostname(int fd, char *name, size_t len)
{
	int rc;
	memset(name, 0, len);
	if (read(fd, name, len-1) >= 0) {
		newline_to_null(name);
		strip_domain(name);
		rc = 0;
	} else {
		syslog(LOG_ERR, "Read %s Failed\n", SYS_HOSTNAME);
		rc = -EIO;
	}
	return rc;
}