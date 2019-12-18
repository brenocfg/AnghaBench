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
struct evhttp_request {struct evbuffer* output_buffer; } ;
struct evbuffer {int dummy; } ;

/* Variables and functions */

struct evbuffer *evhttp_request_get_output_buffer(struct evhttp_request *req)
{
	return (req->output_buffer);
}