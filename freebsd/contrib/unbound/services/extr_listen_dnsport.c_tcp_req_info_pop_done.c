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
struct tcp_req_info {scalar_t__ num_done_req; struct tcp_req_done_item* done_req_list; } ;
struct tcp_req_done_item {struct tcp_req_done_item* next; scalar_t__ len; } ;

/* Variables and functions */
 int /*<<< orphan*/  lock_basic_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lock_basic_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  log_assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stream_wait_count ; 
 int /*<<< orphan*/  stream_wait_count_lock ; 

__attribute__((used)) static struct tcp_req_done_item*
tcp_req_info_pop_done(struct tcp_req_info* req)
{
	struct tcp_req_done_item* item;
	log_assert(req->num_done_req > 0 && req->done_req_list);
	item = req->done_req_list;
	lock_basic_lock(&stream_wait_count_lock);
	stream_wait_count -= (sizeof(struct tcp_req_done_item)+item->len);
	lock_basic_unlock(&stream_wait_count_lock);
	req->done_req_list = req->done_req_list->next;
	req->num_done_req --;
	return item;
}