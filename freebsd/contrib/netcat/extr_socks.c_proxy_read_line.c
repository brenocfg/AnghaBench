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
 int atomicio (int /*<<< orphan*/ ,int,char*,int) ; 
 int /*<<< orphan*/  err (int,char*) ; 
 int /*<<< orphan*/  errx (int,char*) ; 
 int /*<<< orphan*/  read ; 

__attribute__((used)) static int
proxy_read_line(int fd, char *buf, size_t bufsz)
{
	size_t off;

	for(off = 0;;) {
		if (off >= bufsz)
			errx(1, "proxy read too long");
		if (atomicio(read, fd, buf + off, 1) != 1)
			err(1, "proxy read");
		/* Skip CR */
		if (buf[off] == '\r')
			continue;
		if (buf[off] == '\n') {
			buf[off] = '\0';
			break;
		}
		off++;
	}
	return (off);
}