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
struct session {int /*<<< orphan*/  client_bufev; int /*<<< orphan*/  id; } ;

/* Variables and functions */
 int /*<<< orphan*/  LOG_DEBUG ; 
 int /*<<< orphan*/  bufferevent_write (int /*<<< orphan*/ ,char*,scalar_t__) ; 
 char* linebuf ; 
 scalar_t__ linelen ; 
 int /*<<< orphan*/  logmsg (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*) ; 
 scalar_t__ strcasecmp (char*,char*) ; 
 scalar_t__ strlen (char*) ; 

int
client_parse_anon(struct session *s)
{
	if (strcasecmp("USER ftp\r\n", linebuf) != 0 &&
	    strcasecmp("USER anonymous\r\n", linebuf) != 0) {
		snprintf(linebuf, sizeof linebuf,
		    "500 Only anonymous FTP allowed\r\n");
		logmsg(LOG_DEBUG, "#%d proxy: %s", s->id, linebuf);

		/* Talk back to the client ourself. */
		linelen = strlen(linebuf);
		bufferevent_write(s->client_bufev, linebuf, linelen);

		/* Clear buffer so it's not sent to the server. */
		linebuf[0] = '\0';
		linelen = 0;
	}

	return (1);
}