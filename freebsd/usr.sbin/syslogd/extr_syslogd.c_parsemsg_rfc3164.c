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
typedef  scalar_t__ time_t ;
struct tm {int tm_year; int tm_isdst; } ;
struct logtime {struct tm tm; scalar_t__ usec; } ;
typedef  int /*<<< orphan*/  line ;

/* Variables and functions */
 int /*<<< orphan*/  MAXHOSTNAMELEN ; 
 int /*<<< orphan*/  MAXLINE ; 
 size_t MIN (int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  RFC3164_DATEFMT ; 
 int RFC3164_DATELEN ; 
 int /*<<< orphan*/  RemoteAddDate ; 
 scalar_t__ RemoteHostname ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  dprintf (char*,char const*,char*) ; 
 int /*<<< orphan*/  localtime_r (scalar_t__*,struct tm*) ; 
 int /*<<< orphan*/  logmsg (int,struct logtime const*,char const*,char const*,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 scalar_t__ mktime (struct tm*) ; 
 int /*<<< orphan*/  parsemsg_remove_unsafe_characters (char*,char*,int) ; 
 int /*<<< orphan*/  parsemsg_rfc3164_app_name_procid (char**,char const**,char const**) ; 
 size_t strlen (char*) ; 
 char* strptime (char*,int /*<<< orphan*/ ,struct tm*) ; 
 scalar_t__ time (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
parsemsg_rfc3164(const char *from, int pri, char *msg)
{
	struct tm tm_parsed;
	const struct logtime *timestamp;
	struct logtime timestamp_remote;
	const char *app_name, *procid;
	size_t i, msglen;
	char line[MAXLINE + 1];

	/*
	 * Parse the TIMESTAMP provided by the remote side. If none is
	 * found, assume this is not an RFC 3164 formatted message,
	 * only containing a TAG and a MSG.
	 */
	timestamp = NULL;
	if (strptime(msg, RFC3164_DATEFMT, &tm_parsed) ==
	    msg + RFC3164_DATELEN && msg[RFC3164_DATELEN] == ' ') {
		msg += RFC3164_DATELEN + 1;
		if (!RemoteAddDate) {
			struct tm tm_now;
			time_t t_now;
			int year;

			/*
			 * As the timestamp does not contain the year
			 * number, daylight saving time information, nor
			 * a time zone, attempt to infer it. Due to
			 * clock skews, the timestamp may even be part
			 * of the next year. Use the last year for which
			 * the timestamp is at most one week in the
			 * future.
			 *
			 * This loop can only run for at most three
			 * iterations before terminating.
			 */
			t_now = time(NULL);
			localtime_r(&t_now, &tm_now);
			for (year = tm_now.tm_year + 1;; --year) {
				assert(year >= tm_now.tm_year - 1);
				timestamp_remote.tm = tm_parsed;
				timestamp_remote.tm.tm_year = year;
				timestamp_remote.tm.tm_isdst = -1;
				timestamp_remote.usec = 0;
				if (mktime(&timestamp_remote.tm) <
				    t_now + 7 * 24 * 60 * 60)
					break;
			}
			timestamp = &timestamp_remote;
		}

		/*
		 * A single space character MUST also follow the HOSTNAME field.
		 */
		msglen = strlen(msg);
		for (i = 0; i < MIN(MAXHOSTNAMELEN, msglen); i++) {
			if (msg[i] == ' ') {
				if (RemoteHostname) {
					msg[i] = '\0';
					from = msg;
				}
				msg += i + 1;
				break;
			}
			/*
			 * Support non RFC compliant messages, without hostname.
			 */
			if (msg[i] == ':')
				break;
		}
		if (i == MIN(MAXHOSTNAMELEN, msglen)) {
			dprintf("Invalid HOSTNAME from %s: %s\n", from, msg);
			return;
		}
	}

	/* Remove the TAG, if present. */
	parsemsg_rfc3164_app_name_procid(&msg, &app_name, &procid);
	parsemsg_remove_unsafe_characters(msg, line, sizeof(line));
	logmsg(pri, timestamp, from, app_name, procid, NULL, NULL, line, 0);
}