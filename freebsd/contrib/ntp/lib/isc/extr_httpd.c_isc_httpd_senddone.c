#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_4__ ;
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  isc_task_t ;
struct TYPE_13__ {scalar_t__ result; int /*<<< orphan*/  bufferlist; } ;
typedef  TYPE_1__ isc_socketevent_t ;
struct TYPE_14__ {unsigned char* base; scalar_t__ length; } ;
typedef  TYPE_2__ isc_region_t ;
struct TYPE_15__ {int flags; int /*<<< orphan*/  sock; scalar_t__ recvbuf; int /*<<< orphan*/  bodybuffer; int /*<<< orphan*/  freecb_arg; int /*<<< orphan*/  (* freecb ) (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ;int /*<<< orphan*/  headerbuffer; } ;
typedef  TYPE_3__ isc_httpd_t ;
struct TYPE_16__ {TYPE_3__* ev_arg; } ;
typedef  TYPE_4__ isc_event_t ;
typedef  int /*<<< orphan*/  isc_buffer_t ;

/* Variables and functions */
 int /*<<< orphan*/  ENTER (char*) ; 
 int /*<<< orphan*/  EXIT (char*) ; 
 int HTTPD_CLOSE ; 
 scalar_t__ HTTP_RECVLEN ; 
 int /*<<< orphan*/  INSIST (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ISC_HTTPD_ISSEND (TYPE_3__*) ; 
 int /*<<< orphan*/  ISC_HTTPD_SETRECV (TYPE_3__*) ; 
 scalar_t__ ISC_LINK_LINKED (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ISC_LIST_UNLINK (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ ISC_R_SUCCESS ; 
 int /*<<< orphan*/  NOTICE (char*) ; 
 int /*<<< orphan*/  destroy_client (TYPE_3__**) ; 
 scalar_t__ isc_buffer_length (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  isc_event_free (TYPE_4__**) ; 
 int /*<<< orphan*/  isc_httpd_recvdone ; 
 int /*<<< orphan*/  isc_socket_recv (int /*<<< orphan*/ ,TYPE_2__*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_3__*) ; 
 int /*<<< orphan*/  link ; 
 int /*<<< orphan*/  reset_client (TYPE_3__*) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
isc_httpd_senddone(isc_task_t *task, isc_event_t *ev)
{
	isc_httpd_t *httpd = ev->ev_arg;
	isc_region_t r;
	isc_socketevent_t *sev = (isc_socketevent_t *)ev;

	ENTER("senddone");
	INSIST(ISC_HTTPD_ISSEND(httpd));

	/*
	 * First, unlink our header buffer from the socket's bufflist.  This
	 * is sort of an evil hack, since we know our buffer will be there,
	 * and we know it's address, so we can just remove it directly.
	 */
	NOTICE("senddone unlinked header");
	ISC_LIST_UNLINK(sev->bufferlist, &httpd->headerbuffer, link);

	/*
	 * We will always want to clean up our receive buffer, even if we
	 * got an error on send or we are shutting down.
	 *
	 * We will pass in the buffer only if there is data in it.  If
	 * there is no data, we will pass in a NULL.
	 */
	if (httpd->freecb != NULL) {
		isc_buffer_t *b = NULL;
		if (isc_buffer_length(&httpd->bodybuffer) > 0)
			b = &httpd->bodybuffer;
		httpd->freecb(b, httpd->freecb_arg);
		NOTICE("senddone free callback performed");
	}
	if (ISC_LINK_LINKED(&httpd->bodybuffer, link)) {
		ISC_LIST_UNLINK(sev->bufferlist, &httpd->bodybuffer, link);
		NOTICE("senddone body buffer unlinked");
	}

	if (sev->result != ISC_R_SUCCESS) {
		destroy_client(&httpd);
		goto out;
	}

	if ((httpd->flags & HTTPD_CLOSE) != 0) {
		destroy_client(&httpd);
		goto out;
	}

	ISC_HTTPD_SETRECV(httpd);

	NOTICE("senddone restarting recv on socket");

	reset_client(httpd);

	r.base = (unsigned char *)httpd->recvbuf;
	r.length = HTTP_RECVLEN - 1;
	/* check return code? */
	(void)isc_socket_recv(httpd->sock, &r, 1, task,
			      isc_httpd_recvdone, httpd);

out:
	isc_event_free(&ev);
	EXIT("senddone");
}