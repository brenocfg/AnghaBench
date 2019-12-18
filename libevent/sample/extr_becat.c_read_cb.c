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
struct evbuffer {int dummy; } ;
struct context {int /*<<< orphan*/  fout; } ;
struct bufferevent {int dummy; } ;

/* Variables and functions */
 struct evbuffer* bufferevent_get_input (struct bufferevent*) ; 
 int /*<<< orphan*/  evbuffer_write (struct evbuffer*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fileno (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void read_cb(struct bufferevent *bev, void *arg)
{
	struct context *ctx = arg;
	struct evbuffer *in = bufferevent_get_input(bev);
	evbuffer_write(in, fileno(ctx->fout));
}