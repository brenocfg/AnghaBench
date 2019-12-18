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
 int /*<<< orphan*/  evhttp_send_reply_chunk_with_cb (struct evhttp_request*,struct evbuffer*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

void
evhttp_send_reply_chunk(struct evhttp_request *req, struct evbuffer *databuf)
{
	evhttp_send_reply_chunk_with_cb(req, databuf, NULL, NULL);
}