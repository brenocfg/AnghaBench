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
struct evhttp_request {int response_code; scalar_t__ type; } ;

/* Variables and functions */
 scalar_t__ EVHTTP_REQ_HEAD ; 
 int HTTP_NOCONTENT ; 
 int HTTP_NOTMODIFIED ; 

__attribute__((used)) static int
evhttp_response_needs_body(struct evhttp_request *req)
{
	return (req->response_code != HTTP_NOCONTENT &&
		req->response_code != HTTP_NOTMODIFIED &&
		(req->response_code < 100 || req->response_code >= 200) &&
		req->type != EVHTTP_REQ_HEAD);
}