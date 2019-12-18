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
struct bufferevent_filter_data_stuck {size_t total_read; } ;
struct bufferevent {int dummy; } ;

/* Variables and functions */
 struct evbuffer* bufferevent_get_input (struct bufferevent*) ; 
 int /*<<< orphan*/  evbuffer_drain (struct evbuffer*,size_t) ; 
 size_t evbuffer_get_length (struct evbuffer*) ; 

__attribute__((used)) static void
bufferevent_filter_data_stuck_readcb(struct bufferevent *bev, void *arg)
{
	struct bufferevent_filter_data_stuck *filter_data = arg;
	struct evbuffer *input = bufferevent_get_input(bev);
	size_t read_size = evbuffer_get_length(input);
	evbuffer_drain(input, read_size);
	filter_data->total_read += read_size;
}