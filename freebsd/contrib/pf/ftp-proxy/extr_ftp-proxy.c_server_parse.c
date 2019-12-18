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
 scalar_t__ CMD_EPSV ; 
 scalar_t__ CMD_NONE ; 
 scalar_t__ CMD_PASV ; 
 int allow_data_connection (struct session*) ; 
 char* linebuf ; 
 int linelen ; 
 scalar_t__ strncmp (char*,char*,int) ; 

int
server_parse(struct session *s)
{
	if (s->cmd == CMD_NONE || linelen < 4 || linebuf[0] != '2')
		goto out;

	if ((s->cmd == CMD_PASV && strncmp("227 ", linebuf, 4) == 0) ||
	    (s->cmd == CMD_EPSV && strncmp("229 ", linebuf, 4) == 0))
		return (allow_data_connection(s));

 out:
	s->cmd = CMD_NONE;
	s->port = 0;

	return (1);
}