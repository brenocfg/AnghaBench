#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_29__   TYPE_6__ ;
typedef  struct TYPE_28__   TYPE_5__ ;
typedef  struct TYPE_27__   TYPE_4__ ;
typedef  struct TYPE_26__   TYPE_3__ ;
typedef  struct TYPE_25__   TYPE_2__ ;
typedef  struct TYPE_24__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  isc_time_t ;
typedef  int /*<<< orphan*/  isc_task_t ;
struct TYPE_25__ {scalar_t__ result; int /*<<< orphan*/  n; } ;
typedef  TYPE_2__ isc_socketevent_t ;
typedef  scalar_t__ isc_result_t ;
struct TYPE_26__ {unsigned char* base; int length; } ;
typedef  TYPE_3__ isc_region_t ;
struct TYPE_27__ {scalar_t__ (* action ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,char**,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ;int /*<<< orphan*/  action_arg; int /*<<< orphan*/  url; } ;
typedef  TYPE_4__ isc_httpdurl_t ;
struct TYPE_28__ {int recvlen; char* mimetype; int /*<<< orphan*/  bufflist; int /*<<< orphan*/  sock; int /*<<< orphan*/  bodybuffer; int /*<<< orphan*/  headerbuffer; int /*<<< orphan*/  freecb_arg; int /*<<< orphan*/  freecb; int /*<<< orphan*/  retmsg; int /*<<< orphan*/  retcode; int /*<<< orphan*/  querystring; int /*<<< orphan*/  url; TYPE_1__* mgr; scalar_t__ recvbuf; } ;
typedef  TYPE_5__ isc_httpd_t ;
struct TYPE_29__ {TYPE_5__* ev_arg; } ;
typedef  TYPE_6__ isc_event_t ;
typedef  int /*<<< orphan*/  datebuf ;
struct TYPE_24__ {scalar_t__ (* render_404 ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,char**,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ;scalar_t__ (* render_500 ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,char**,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ;int /*<<< orphan*/  urls; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENTER (char*) ; 
 int /*<<< orphan*/  EXIT (char*) ; 
 int HTTP_RECVLEN ; 
 int /*<<< orphan*/  INSIST (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ISC_HTTPD_ISRECV (TYPE_5__*) ; 
 int /*<<< orphan*/  ISC_HTTPD_SETSEND (TYPE_5__*) ; 
 int /*<<< orphan*/  ISC_LIST_APPEND (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 TYPE_4__* ISC_LIST_HEAD (int /*<<< orphan*/ ) ; 
 TYPE_4__* ISC_LIST_NEXT (TYPE_4__*,int /*<<< orphan*/ ) ; 
 scalar_t__ ISC_R_NOTFOUND ; 
 scalar_t__ ISC_R_SUCCESS ; 
 int /*<<< orphan*/  NOTICE (char*) ; 
 int /*<<< orphan*/  RUNTIME_CHECK (int) ; 
 int /*<<< orphan*/  destroy_client (TYPE_5__**) ; 
 int /*<<< orphan*/  isc_buffer_initnull (int /*<<< orphan*/ *) ; 
 scalar_t__ isc_buffer_length (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  isc_buffer_usedlength (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  isc_event_free (TYPE_6__**) ; 
 int /*<<< orphan*/  isc_httpd_addheader (TYPE_5__*,char*,char*) ; 
 int /*<<< orphan*/  isc_httpd_addheaderuint (TYPE_5__*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  isc_httpd_endheaders (TYPE_5__*) ; 
 int /*<<< orphan*/  isc_httpd_response (TYPE_5__*) ; 
 int /*<<< orphan*/  isc_httpd_senddone ; 
 int /*<<< orphan*/  isc_socket_recv (int /*<<< orphan*/ ,TYPE_3__*,int,int /*<<< orphan*/ *,void (*) (int /*<<< orphan*/ *,TYPE_6__*),TYPE_5__*) ; 
 int /*<<< orphan*/  isc_socket_sendv (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_5__*) ; 
 int /*<<< orphan*/  isc_time_formathttptimestamp (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  isc_time_now (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  link ; 
 scalar_t__ process_request (TYPE_5__*,int /*<<< orphan*/ ) ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,char**,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ stub2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,char**,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ stub3 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,char**,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
isc_httpd_recvdone(isc_task_t *task, isc_event_t *ev)
{
	isc_region_t r;
	isc_result_t result;
	isc_httpd_t *httpd = ev->ev_arg;
	isc_socketevent_t *sev = (isc_socketevent_t *)ev;
	isc_httpdurl_t *url;
	isc_time_t now;
	char datebuf[32];  /* Only need 30, but safety first */

	ENTER("recv");

	INSIST(ISC_HTTPD_ISRECV(httpd));

	if (sev->result != ISC_R_SUCCESS) {
		NOTICE("recv destroying client");
		destroy_client(&httpd);
		goto out;
	}

	result = process_request(httpd, sev->n);
	if (result == ISC_R_NOTFOUND) {
		if (httpd->recvlen >= HTTP_RECVLEN - 1) {
			destroy_client(&httpd);
			goto out;
		}
		r.base = (unsigned char *)httpd->recvbuf + httpd->recvlen;
		r.length = HTTP_RECVLEN - httpd->recvlen - 1;
		/* check return code? */
		(void)isc_socket_recv(httpd->sock, &r, 1, task,
				      isc_httpd_recvdone, httpd);
		goto out;
	} else if (result != ISC_R_SUCCESS) {
		destroy_client(&httpd);
		goto out;
	}

	ISC_HTTPD_SETSEND(httpd);

	/*
	 * XXXMLG Call function here.  Provide an add-header function
	 * which will append the common headers to a response we generate.
	 */
	isc_buffer_initnull(&httpd->bodybuffer);
	isc_time_now(&now);
	isc_time_formathttptimestamp(&now, datebuf, sizeof(datebuf));
	url = ISC_LIST_HEAD(httpd->mgr->urls);
	while (url != NULL) {
		if (strcmp(httpd->url, url->url) == 0)
			break;
		url = ISC_LIST_NEXT(url, link);
	}
	if (url == NULL)
		result = httpd->mgr->render_404(httpd->url, httpd->querystring,
						NULL,
						&httpd->retcode,
						&httpd->retmsg,
						&httpd->mimetype,
						&httpd->bodybuffer,
						&httpd->freecb,
						&httpd->freecb_arg);
	else
		result = url->action(httpd->url, httpd->querystring,
				     url->action_arg,
				     &httpd->retcode, &httpd->retmsg,
				     &httpd->mimetype, &httpd->bodybuffer,
				     &httpd->freecb, &httpd->freecb_arg);
	if (result != ISC_R_SUCCESS) {
		result = httpd->mgr->render_500(httpd->url, httpd->querystring,
						NULL, &httpd->retcode,
						&httpd->retmsg,
						&httpd->mimetype,
						&httpd->bodybuffer,
						&httpd->freecb,
						&httpd->freecb_arg);
		RUNTIME_CHECK(result == ISC_R_SUCCESS);
	}

	isc_httpd_response(httpd);
	isc_httpd_addheader(httpd, "Content-Type", httpd->mimetype);
	isc_httpd_addheader(httpd, "Date", datebuf);
	isc_httpd_addheader(httpd, "Expires", datebuf);
	isc_httpd_addheader(httpd, "Last-Modified", datebuf);
	isc_httpd_addheader(httpd, "Pragma: no-cache", NULL);
	isc_httpd_addheader(httpd, "Cache-Control: no-cache", NULL);
	isc_httpd_addheader(httpd, "Server: libisc", NULL);
	isc_httpd_addheaderuint(httpd, "Content-Length",
				isc_buffer_usedlength(&httpd->bodybuffer));
	isc_httpd_endheaders(httpd);  /* done */

	ISC_LIST_APPEND(httpd->bufflist, &httpd->headerbuffer, link);
	/*
	 * Link the data buffer into our send queue, should we have any data
	 * rendered into it.  If no data is present, we won't do anything
	 * with the buffer.
	 */
	if (isc_buffer_length(&httpd->bodybuffer) > 0)
		ISC_LIST_APPEND(httpd->bufflist, &httpd->bodybuffer, link);

	/* check return code? */
	(void)isc_socket_sendv(httpd->sock, &httpd->bufflist, task,
			       isc_httpd_senddone, httpd);

 out:
	isc_event_free(&ev);
	EXIT("recv");
}