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
struct evkeyvalq {int dummy; } ;
struct evhttp_request {struct evkeyvalq* output_headers; } ;

/* Variables and functions */

struct evkeyvalq *evhttp_request_get_output_headers(struct evhttp_request *req)
{
	return (req->output_headers);
}