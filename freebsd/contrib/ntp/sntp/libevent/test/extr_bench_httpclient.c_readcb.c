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
struct request_info {size_t n_read; } ;
struct evbuffer {int dummy; } ;
struct bufferevent {int dummy; } ;

/* Variables and functions */
 struct evbuffer* bufferevent_get_input (struct bufferevent*) ; 
 int /*<<< orphan*/  evbuffer_drain (struct evbuffer*,size_t) ; 
 size_t evbuffer_get_length (struct evbuffer*) ; 

__attribute__((used)) static void
readcb(struct bufferevent *b, void *arg)
{
	struct request_info *ri = arg;
	struct evbuffer *input = bufferevent_get_input(b);
	size_t n = evbuffer_get_length(input);

	ri->n_read += n;
	evbuffer_drain(input, n);
}