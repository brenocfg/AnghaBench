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
typedef  int /*<<< orphan*/  timebuf ;
typedef  int suseconds_t ;
struct iovlist {int dummy; } ;
struct TYPE_2__ {int usec; int /*<<< orphan*/  tm; } ;
struct filed {scalar_t__ f_type; int f_prevpri; TYPE_1__ f_lasttime; } ;
typedef  int /*<<< orphan*/  priority_number ;

/* Variables and functions */
 scalar_t__ F_WALL ; 
 int /*<<< orphan*/  fprintlog_write (struct filed*,struct iovlist*,int) ; 
 int /*<<< orphan*/  iovlist_append (struct iovlist*,char const*) ; 
 int /*<<< orphan*/  iovlist_init (struct iovlist*) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,int) ; 
 int strftime (char*,int,char*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
fprintlog_rfc5424(struct filed *f, const char *hostname, const char *app_name,
    const char *procid, const char *msgid, const char *structured_data,
    const char *msg, int flags)
{
	struct iovlist il;
	suseconds_t usec;
	int i;
	char timebuf[33], priority_number[5];

	iovlist_init(&il);
	if (f->f_type == F_WALL)
		iovlist_append(&il, "\r\n\aMessage from syslogd ...\r\n");
	iovlist_append(&il, "<");
	snprintf(priority_number, sizeof(priority_number), "%d", f->f_prevpri);
	iovlist_append(&il, priority_number);
	iovlist_append(&il, ">1 ");
	if (strftime(timebuf, sizeof(timebuf), "%FT%T.______%z",
	    &f->f_lasttime.tm) == sizeof(timebuf) - 2) {
		/* Add colon to the time zone offset, which %z doesn't do. */
		timebuf[32] = '\0';
		timebuf[31] = timebuf[30];
		timebuf[30] = timebuf[29];
		timebuf[29] = ':';

		/* Overwrite space for microseconds with actual value. */
		usec = f->f_lasttime.usec;
		for (i = 25; i >= 20; --i) {
			timebuf[i] = usec % 10 + '0';
			usec /= 10;
		}
		iovlist_append(&il, timebuf);
	} else
		iovlist_append(&il, "-");
	iovlist_append(&il, " ");
	iovlist_append(&il, hostname);
	iovlist_append(&il, " ");
	iovlist_append(&il, app_name == NULL ? "-" : app_name);
	iovlist_append(&il, " ");
	iovlist_append(&il, procid == NULL ? "-" : procid);
	iovlist_append(&il, " ");
	iovlist_append(&il, msgid == NULL ? "-" : msgid);
	iovlist_append(&il, " ");
	iovlist_append(&il, structured_data == NULL ? "-" : structured_data);
	iovlist_append(&il, " ");
	iovlist_append(&il, msg);

	fprintlog_write(f, &il, flags);
}