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
struct timeval {int member_1; int /*<<< orphan*/  member_0; } ;
struct evhttp_request {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  EV_TIMEOUT ; 
 int /*<<< orphan*/  event_base_once (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct evhttp_request*,struct timeval*) ; 
 int /*<<< orphan*/  exit_base ; 
 int /*<<< orphan*/  http_timeout_reply_cb ; 

__attribute__((used)) static void
http_timeout_cb(struct evhttp_request *req, void *arg)
{
	struct timeval when = { 0, 100 };
	event_base_once(exit_base, -1, EV_TIMEOUT,
	    http_timeout_reply_cb, req, &when);
}