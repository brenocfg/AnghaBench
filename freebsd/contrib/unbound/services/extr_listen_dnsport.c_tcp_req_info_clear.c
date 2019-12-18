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
struct tcp_req_open_item {struct tcp_req_open_item* buf; scalar_t__ len; struct tcp_req_open_item* next; int /*<<< orphan*/  mesh_state; int /*<<< orphan*/  mesh; } ;
struct tcp_req_info {scalar_t__ read_is_closed; scalar_t__ num_done_req; struct tcp_req_open_item* done_req_list; scalar_t__ num_open_req; struct tcp_req_open_item* open_req_list; int /*<<< orphan*/  cp; } ;
struct tcp_req_done_item {struct tcp_req_done_item* buf; scalar_t__ len; struct tcp_req_done_item* next; int /*<<< orphan*/  mesh_state; int /*<<< orphan*/  mesh; } ;

/* Variables and functions */
 int /*<<< orphan*/  free (struct tcp_req_open_item*) ; 
 int /*<<< orphan*/  lock_basic_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lock_basic_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mesh_state_remove_reply (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stream_wait_count ; 
 int /*<<< orphan*/  stream_wait_count_lock ; 

void tcp_req_info_clear(struct tcp_req_info* req)
{
	struct tcp_req_open_item* open, *nopen;
	struct tcp_req_done_item* item, *nitem;
	if(!req) return;

	/* free outstanding request mesh reply entries */
	open = req->open_req_list;
	while(open) {
		nopen = open->next;
		mesh_state_remove_reply(open->mesh, open->mesh_state, req->cp);
		free(open);
		open = nopen;
	}
	req->open_req_list = NULL;
	req->num_open_req = 0;
	
	/* free pending writable result packets */
	item = req->done_req_list;
	while(item) {
		nitem = item->next;
		lock_basic_lock(&stream_wait_count_lock);
		stream_wait_count -= (sizeof(struct tcp_req_done_item)
			+item->len);
		lock_basic_unlock(&stream_wait_count_lock);
		free(item->buf);
		free(item);
		item = nitem;
	}
	req->done_req_list = NULL;
	req->num_done_req = 0;
	req->read_is_closed = 0;
}