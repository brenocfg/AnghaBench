#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int ssize_t ;
struct TYPE_9__ {int len; int /*<<< orphan*/  buf; } ;
typedef  TYPE_1__ packet_t ;
struct TYPE_10__ {int (* recv ) (TYPE_1__*) ;int /*<<< orphan*/  mru; } ;
typedef  TYPE_2__ channel_t ;

/* Variables and functions */
 int /*<<< orphan*/  channel_close (TYPE_2__*) ; 
 int /*<<< orphan*/  channel_dispatch (TYPE_1__*) ; 
 int /*<<< orphan*/  log_debug (char*,int) ; 
 int /*<<< orphan*/  log_err (char*) ; 
 TYPE_1__* packet_alloc (TYPE_2__*) ; 
 int /*<<< orphan*/  packet_free (TYPE_1__*) ; 
 int read (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int stub1 (TYPE_1__*) ; 

__attribute__((used)) static void
channel_read(int fd, short ev, void *arg)
{
	channel_t *chan = arg;
	packet_t *pkt;
	ssize_t nr;

	pkt = packet_alloc(chan);
	if (pkt == NULL) {
		channel_close(chan);
		return;
	}

	nr = read(fd, pkt->buf, chan->mru);
	if (nr == -1) {
		log_err("channel read error: %m");
		packet_free(pkt);
		channel_close(chan);
		return;
	}
	if (nr == 0) {	/* EOF */
		log_debug("(fd#%d) EOF", fd);
		packet_free(pkt);
		channel_close(chan);
		return;
	}
	pkt->len = nr;

	if (chan->recv(pkt) == true)
		channel_dispatch(pkt);

	packet_free(pkt);
}