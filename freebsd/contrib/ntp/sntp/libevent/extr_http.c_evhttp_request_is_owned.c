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
struct evhttp_request {int flags; } ;

/* Variables and functions */
 int EVHTTP_USER_OWNED ; 

int
evhttp_request_is_owned(struct evhttp_request *req)
{
	return (req->flags & EVHTTP_USER_OWNED) != 0;
}