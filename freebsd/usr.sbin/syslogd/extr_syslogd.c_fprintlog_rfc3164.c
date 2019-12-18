#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  timebuf ;
struct iovlist {int dummy; } ;
struct TYPE_5__ {int /*<<< orphan*/  tm; } ;
struct filed {int f_type; int f_prevpri; TYPE_1__ f_lasttime; } ;
typedef  int /*<<< orphan*/  priority_number ;
typedef  int /*<<< orphan*/  facility_number ;
struct TYPE_6__ {char const* c_name; int c_val; } ;
typedef  TYPE_2__ CODE ;

/* Variables and functions */
#define  F_FORW 129 
#define  F_WALL 128 
 int LOG_FAC (int) ; 
 int LOG_FACMASK ; 
 int LOG_PRI (int) ; 
 int /*<<< orphan*/  LocalHostName ; 
 int LogFacPri ; 
 int /*<<< orphan*/  RFC3164_DATEFMT ; 
 int /*<<< orphan*/  RFC3164_DATELEN ; 
 TYPE_2__* facilitynames ; 
 int /*<<< orphan*/  fprintlog_write (struct filed*,struct iovlist*,int) ; 
 int /*<<< orphan*/  iovlist_append (struct iovlist*,char const*) ; 
 int /*<<< orphan*/  iovlist_init (struct iovlist*) ; 
 TYPE_2__* prioritynames ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,int) ; 
 int /*<<< orphan*/  strcasecmp (char const*,int /*<<< orphan*/ ) ; 
 scalar_t__ strftime (char*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
fprintlog_rfc3164(struct filed *f, const char *hostname, const char *app_name,
    const char *procid, const char *msg, int flags)
{
	struct iovlist il;
	const CODE *c;
	int facility, priority;
	char timebuf[RFC3164_DATELEN + 1], facility_number[5],
	    priority_number[5];
	bool facility_found, priority_found;

	if (strftime(timebuf, sizeof(timebuf), RFC3164_DATEFMT,
	    &f->f_lasttime.tm) == 0)
		timebuf[0] = '\0';

	iovlist_init(&il);
	switch (f->f_type) {
	case F_FORW:
		/* Message forwarded over the network. */
		iovlist_append(&il, "<");
		snprintf(priority_number, sizeof(priority_number), "%d",
		    f->f_prevpri);
		iovlist_append(&il, priority_number);
		iovlist_append(&il, ">");
		iovlist_append(&il, timebuf);
		if (strcasecmp(hostname, LocalHostName) != 0) {
			iovlist_append(&il, " Forwarded from ");
			iovlist_append(&il, hostname);
			iovlist_append(&il, ":");
		}
		iovlist_append(&il, " ");
		break;

	case F_WALL:
		/* Message written to terminals. */
		iovlist_append(&il, "\r\n\aMessage from syslogd@");
		iovlist_append(&il, hostname);
		iovlist_append(&il, " at ");
		iovlist_append(&il, timebuf);
		iovlist_append(&il, " ...\r\n");
		break;

	default:
		/* Message written to files. */
		iovlist_append(&il, timebuf);
		iovlist_append(&il, " ");

		if (LogFacPri) {
			iovlist_append(&il, "<");

			facility = f->f_prevpri & LOG_FACMASK;
			facility_found = false;
			if (LogFacPri > 1) {
				for (c = facilitynames; c->c_name; c++) {
					if (c->c_val == facility) {
						iovlist_append(&il, c->c_name);
						facility_found = true;
						break;
					}
				}
			}
			if (!facility_found) {
				snprintf(facility_number,
				    sizeof(facility_number), "%d",
				    LOG_FAC(facility));
				iovlist_append(&il, facility_number);
			}

			iovlist_append(&il, ".");

			priority = LOG_PRI(f->f_prevpri);
			priority_found = false;
			if (LogFacPri > 1) {
				for (c = prioritynames; c->c_name; c++) {
					if (c->c_val == priority) {
						iovlist_append(&il, c->c_name);
						priority_found = true;
						break;
					}
				}
			}
			if (!priority_found) {
				snprintf(priority_number,
				    sizeof(priority_number), "%d", priority);
				iovlist_append(&il, priority_number);
			}

			iovlist_append(&il, "> ");
		}

		iovlist_append(&il, hostname);
		iovlist_append(&il, " ");
		break;
	}

	/* Message body with application name and process ID prefixed. */
	if (app_name != NULL) {
		iovlist_append(&il, app_name);
		if (procid != NULL) {
			iovlist_append(&il, "[");
			iovlist_append(&il, procid);
			iovlist_append(&il, "]");
		}
		iovlist_append(&il, ": ");
	}
	iovlist_append(&il, msg);

	fprintlog_write(f, &il, flags);
}