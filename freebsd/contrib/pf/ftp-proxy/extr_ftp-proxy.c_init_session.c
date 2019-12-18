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
struct session {int client_fd; int server_fd; char* cbuf; char* sbuf; scalar_t__ port; int /*<<< orphan*/  cmd; int /*<<< orphan*/ * server_bufev; int /*<<< orphan*/ * client_bufev; scalar_t__ sbuf_valid; scalar_t__ cbuf_valid; scalar_t__ id; } ;

/* Variables and functions */
 int /*<<< orphan*/  CMD_NONE ; 
 int /*<<< orphan*/  LIST_INSERT_HEAD (int /*<<< orphan*/ *,struct session*,int /*<<< orphan*/ ) ; 
 struct session* calloc (int,int) ; 
 int /*<<< orphan*/  entry ; 
 int /*<<< orphan*/  id_count ; 
 int /*<<< orphan*/  session_count ; 
 int /*<<< orphan*/  sessions ; 

struct session *
init_session(void)
{
	struct session *s;

	s = calloc(1, sizeof(struct session));
	if (s == NULL)
		return (NULL);

	s->id = id_count++;
	s->client_fd = -1;
	s->server_fd = -1;
	s->cbuf[0] = '\0';
	s->cbuf_valid = 0;
	s->sbuf[0] = '\0';
	s->sbuf_valid = 0;
	s->client_bufev = NULL;
	s->server_bufev = NULL;
	s->cmd = CMD_NONE;
	s->port = 0;

	LIST_INSERT_HEAD(&sessions, s, entry);
	session_count++;

	return (s);
}