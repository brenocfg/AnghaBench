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
struct terminate_state {int gotclosecb; } ;
struct evhttp_connection {int dummy; } ;

/* Variables and functions */

__attribute__((used)) static void
terminate_chunked_close_cb(struct evhttp_connection *evcon, void *arg)
{
	struct terminate_state *state = arg;
	state->gotclosecb = 1;
}