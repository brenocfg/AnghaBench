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
struct bufferevent {int /*<<< orphan*/  enabled; void* cbarg; int /*<<< orphan*/  errorcb; void* writecb; void* readcb; int /*<<< orphan*/  ev_write; int /*<<< orphan*/  ev_read; int /*<<< orphan*/ * input; int /*<<< orphan*/ * output; } ;
typedef  int /*<<< orphan*/  everrorcb ;
typedef  void* evbuffercb ;

/* Variables and functions */
 int /*<<< orphan*/  EV_READ ; 
 int /*<<< orphan*/  EV_WRITE ; 
 int /*<<< orphan*/  bufferevent_readcb ; 
 int /*<<< orphan*/  bufferevent_writecb ; 
 struct bufferevent* calloc (int,int) ; 
 int /*<<< orphan*/  evbuffer_free (int /*<<< orphan*/ *) ; 
 void* evbuffer_new () ; 
 int /*<<< orphan*/  event_set (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct bufferevent*) ; 
 int /*<<< orphan*/  free (struct bufferevent*) ; 

struct bufferevent *
bufferevent_new(int fd, evbuffercb readcb, evbuffercb writecb,
    everrorcb errorcb, void *cbarg)
{
	struct bufferevent *bufev;

	if ((bufev = calloc(1, sizeof(struct bufferevent))) == NULL)
		return (NULL);

	if ((bufev->input = evbuffer_new()) == NULL) {
		free(bufev);
		return (NULL);
	}

	if ((bufev->output = evbuffer_new()) == NULL) {
		evbuffer_free(bufev->input);
		free(bufev);
		return (NULL);
	}

	event_set(&bufev->ev_read, fd, EV_READ, bufferevent_readcb, bufev);
	event_set(&bufev->ev_write, fd, EV_WRITE, bufferevent_writecb, bufev);

	bufev->readcb = readcb;
	bufev->writecb = writecb;
	bufev->errorcb = errorcb;

	bufev->cbarg = cbarg;

	/*
	 * Set to EV_WRITE so that using bufferevent_write is going to
	 * trigger a callback.  Reading needs to be explicitly enabled
	 * because otherwise no data will be available.
	 */
	bufev->enabled = EV_WRITE;

	return (bufev);
}