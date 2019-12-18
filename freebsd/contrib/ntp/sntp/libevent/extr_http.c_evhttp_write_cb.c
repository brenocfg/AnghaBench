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
struct evhttp_connection {int /*<<< orphan*/  cb_arg; int /*<<< orphan*/  (* cb ) (struct evhttp_connection*,int /*<<< orphan*/ ) ;} ;
struct bufferevent {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (struct evhttp_connection*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
evhttp_write_cb(struct bufferevent *bufev, void *arg)
{
	struct evhttp_connection *evcon = arg;

	/* Activate our call back */
	if (evcon->cb != NULL)
		(*evcon->cb)(evcon, evcon->cb_arg);
}