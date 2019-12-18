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
struct evhttp_request {int /*<<< orphan*/  output_headers; int /*<<< orphan*/  flags; int /*<<< orphan*/  input_headers; } ;

/* Variables and functions */
 scalar_t__ evhttp_is_connection_close (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
evhttp_is_request_connection_close(struct evhttp_request *req)
{
	return
		evhttp_is_connection_close(req->flags, req->input_headers) ||
		evhttp_is_connection_close(req->flags, req->output_headers);
}