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
struct evhttp_request {int dummy; } ;
struct evbuffer {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  evhttp_response_code_ (struct evhttp_request*,int,char const*) ; 
 int /*<<< orphan*/  evhttp_send (struct evhttp_request*,struct evbuffer*) ; 

void
evhttp_send_reply(struct evhttp_request *req, int code, const char *reason,
    struct evbuffer *databuf)
{
	evhttp_response_code_(req, code, reason);

	evhttp_send(req, databuf);
}