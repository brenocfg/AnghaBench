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
typedef  scalar_t__ off_t ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  LOG_ERR ; 
 int buffer ; 
 int /*<<< orphan*/  bufleft ; 
 int /*<<< orphan*/  buflen ; 
 scalar_t__ bufpkt ; 
 int bufpos ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  fileno (int /*<<< orphan*/ *) ; 
 scalar_t__ ftello (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ftruncate (int /*<<< orphan*/ ,scalar_t__) ; 
 int fwrite (int,int,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  logmsg (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_suspended (int) ; 
 int /*<<< orphan*/  strerror (int /*<<< orphan*/ ) ; 

int
flush_buffer(FILE *f)
{
	off_t offset;
	int len = bufpos - buffer;

	if (len <= 0)
		return (0);

	offset = ftello(f);
	if (offset == (off_t)-1) {
		set_suspended(1);
		logmsg(LOG_ERR, "Logging suspended: ftello: %s",
		    strerror(errno));
		return (1);
	}

	if (fwrite(buffer, len, 1, f) != 1) {
		set_suspended(1);
		logmsg(LOG_ERR, "Logging suspended: fwrite: %s",
		    strerror(errno));
		ftruncate(fileno(f), offset);
		return (1);
	}

	set_suspended(0);
	bufpos = buffer;
	bufleft = buflen;
	bufpkt = 0;

	return (0);
}