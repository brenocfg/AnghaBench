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
struct session {int client_fd; int server_fd; int /*<<< orphan*/  id; TYPE_1__* server_bufev; TYPE_1__* client_bufev; } ;
struct TYPE_2__ {int /*<<< orphan*/  output; } ;

/* Variables and functions */
 int /*<<< orphan*/  LIST_REMOVE (struct session*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LOG_ERR ; 
 int /*<<< orphan*/  LOG_INFO ; 
 int /*<<< orphan*/  bufferevent_free (TYPE_1__*) ; 
 int /*<<< orphan*/  close (int) ; 
 int do_commit () ; 
 int /*<<< orphan*/  do_rollback () ; 
 int /*<<< orphan*/  entry ; 
 int errno ; 
 int /*<<< orphan*/  evbuffer_write (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  free (struct session*) ; 
 int /*<<< orphan*/  logmsg (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,...) ; 
 int prepare_commit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  session_count ; 
 int /*<<< orphan*/  strerror (int) ; 

void
end_session(struct session *s)
{
	int serr;

	logmsg(LOG_INFO, "#%d ending session", s->id);

	/* Flush output buffers. */
	if (s->client_bufev && s->client_fd != -1)
		evbuffer_write(s->client_bufev->output, s->client_fd);
	if (s->server_bufev && s->server_fd != -1)
		evbuffer_write(s->server_bufev->output, s->server_fd);

	if (s->client_fd != -1)
		close(s->client_fd);
	if (s->server_fd != -1)
		close(s->server_fd);

	if (s->client_bufev)
		bufferevent_free(s->client_bufev);
	if (s->server_bufev)
		bufferevent_free(s->server_bufev);

	/* Remove rulesets by commiting empty ones. */
	serr = 0;
	if (prepare_commit(s->id) == -1)
		serr = errno;
	else if (do_commit() == -1) {
		serr = errno;
		do_rollback();
	}
	if (serr)
		logmsg(LOG_ERR, "#%d pf rule removal failed: %s", s->id,
		    strerror(serr));

	LIST_REMOVE(s, entry);
	free(s);
	session_count--;
}