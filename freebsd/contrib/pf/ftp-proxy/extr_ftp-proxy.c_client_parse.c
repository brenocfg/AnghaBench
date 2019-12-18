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
struct session {scalar_t__ cmd; scalar_t__ port; } ;

/* Variables and functions */
 scalar_t__ CMD_EPRT ; 
 scalar_t__ CMD_NONE ; 
 scalar_t__ CMD_PORT ; 
 int allow_data_connection (struct session*) ; 
 scalar_t__ anonymous_only ; 
 int client_parse_anon (struct session*) ; 
 int /*<<< orphan*/  client_parse_cmd (struct session*) ; 
 char* linebuf ; 
 int linelen ; 

int
client_parse(struct session *s)
{
	/* Reset any previous command. */
	s->cmd = CMD_NONE;
	s->port = 0;

	/* Commands we are looking for are at least 4 chars long. */
	if (linelen < 4)
		return (1);

	if (linebuf[0] == 'P' || linebuf[0] == 'p' ||
	    linebuf[0] == 'E' || linebuf[0] == 'e') {
		if (!client_parse_cmd(s))
			return (0);

		/*
		 * Allow active mode connections immediately, instead of
		 * waiting for a positive reply from the server.  Some
		 * rare servers/proxies try to probe or setup the data
		 * connection before an actual transfer request.
		 */
		if (s->cmd == CMD_PORT || s->cmd == CMD_EPRT)
			return (allow_data_connection(s));
	}
	
	if (anonymous_only && (linebuf[0] == 'U' || linebuf[0] == 'u'))
		return (client_parse_anon(s));

	return (1);
}