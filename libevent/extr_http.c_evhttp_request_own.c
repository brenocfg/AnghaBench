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
struct evhttp_request {int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  EVHTTP_USER_OWNED ; 

void
evhttp_request_own(struct evhttp_request *req)
{
	req->flags |= EVHTTP_USER_OWNED;
}