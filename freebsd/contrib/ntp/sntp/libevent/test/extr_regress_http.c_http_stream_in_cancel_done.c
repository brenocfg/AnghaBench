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

/* Variables and functions */
 int /*<<< orphan*/  tt_fail_msg (char*) ; 

__attribute__((used)) static void
http_stream_in_cancel_done(struct evhttp_request *req, void *arg)
{
	/* should never be called */
	tt_fail_msg("In cancel done");
}