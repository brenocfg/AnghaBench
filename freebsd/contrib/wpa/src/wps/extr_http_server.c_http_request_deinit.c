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
struct http_server {int /*<<< orphan*/  request_count; struct http_request* requests; } ;
struct http_request {int /*<<< orphan*/  fd; int /*<<< orphan*/  hread; struct http_request* next; struct http_server* srv; } ;

/* Variables and functions */
 int /*<<< orphan*/  close (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  httpread_destroy (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  os_free (struct http_request*) ; 

void http_request_deinit(struct http_request *req)
{
	struct http_request *r, *p;
	struct http_server *srv;

	if (req == NULL)
		return;

	srv = req->srv;
	p = NULL;
	r = srv->requests;
	while (r) {
		if (r == req) {
			if (p)
				p->next = r->next;
			else
				srv->requests = r->next;
			srv->request_count--;
			break;
		}
		p = r;
		r = r->next;
	}

	httpread_destroy(req->hread);
	close(req->fd);
	os_free(req);
}