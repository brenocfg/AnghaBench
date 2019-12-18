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
struct sockaddr_in {int dummy; } ;
struct http_server {scalar_t__ request_count; } ;
struct http_request {int fd; int /*<<< orphan*/ * hread; struct sockaddr_in cli; struct http_server* srv; } ;

/* Variables and functions */
 scalar_t__ HTTP_SERVER_MAX_CONNECTIONS ; 
 int /*<<< orphan*/  HTTP_SERVER_MAX_REQ_LEN ; 
 int /*<<< orphan*/  HTTP_SERVER_TIMEOUT ; 
 int /*<<< orphan*/  MSG_DEBUG ; 
 int /*<<< orphan*/  http_request_cb ; 
 int /*<<< orphan*/  http_request_deinit (struct http_request*) ; 
 int /*<<< orphan*/ * httpread_create (int,int /*<<< orphan*/ ,struct http_request*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct http_request* os_zalloc (int) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static struct http_request * http_request_init(struct http_server *srv, int fd,
					       struct sockaddr_in *cli)
{
	struct http_request *req;

	if (srv->request_count >= HTTP_SERVER_MAX_CONNECTIONS) {
		wpa_printf(MSG_DEBUG, "HTTP: Too many concurrent requests");
		return NULL;
	}

	req = os_zalloc(sizeof(*req));
	if (req == NULL)
		return NULL;

	req->srv = srv;
	req->fd = fd;
	req->cli = *cli;

	req->hread = httpread_create(req->fd, http_request_cb, req,
				     HTTP_SERVER_MAX_REQ_LEN,
				     HTTP_SERVER_TIMEOUT);
	if (req->hread == NULL) {
		http_request_deinit(req);
		return NULL;
	}

	return req;
}