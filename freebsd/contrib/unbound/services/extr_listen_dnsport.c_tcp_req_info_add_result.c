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
typedef  int /*<<< orphan*/  uint8_t ;
struct tcp_req_info {int /*<<< orphan*/  num_done_req; struct tcp_req_done_item* done_req_list; } ;
struct tcp_req_done_item {size_t len; struct tcp_req_done_item* next; int /*<<< orphan*/  buf; } ;

/* Variables and functions */
 int /*<<< orphan*/  VERB_ALGO ; 
 int /*<<< orphan*/  free (struct tcp_req_done_item*) ; 
 int /*<<< orphan*/  lock_basic_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lock_basic_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  log_err (char*) ; 
 scalar_t__ malloc (int) ; 
 int /*<<< orphan*/  memdup (int /*<<< orphan*/ *,size_t) ; 
 scalar_t__ stream_wait_count ; 
 int /*<<< orphan*/  stream_wait_count_lock ; 
 scalar_t__ stream_wait_max ; 
 int /*<<< orphan*/  verbose (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int
tcp_req_info_add_result(struct tcp_req_info* req, uint8_t* buf, size_t len)
{
	struct tcp_req_done_item* last = NULL;
	struct tcp_req_done_item* item;
	size_t space;

	/* see if we have space */
	space = sizeof(struct tcp_req_done_item) + len;
	lock_basic_lock(&stream_wait_count_lock);
	if(stream_wait_count + space > stream_wait_max) {
		lock_basic_unlock(&stream_wait_count_lock);
		verbose(VERB_ALGO, "drop stream reply, no space left, in stream-wait-size");
		return 0;
	}
	stream_wait_count += space;
	lock_basic_unlock(&stream_wait_count_lock);

	/* find last element */
	last = req->done_req_list;
	while(last && last->next)
		last = last->next;
	
	/* create new element */
	item = (struct tcp_req_done_item*)malloc(sizeof(*item));
	if(!item) {
		log_err("malloc failure, for stream result list");
		return 0;
	}
	item->next = NULL;
	item->len = len;
	item->buf = memdup(buf, len);
	if(!item->buf) {
		free(item);
		log_err("malloc failure, adding reply to stream result list");
		return 0;
	}

	/* link in */
	if(last) last->next = item;
	else req->done_req_list = item;
	req->num_done_req++;
	return 1;
}