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
struct tcp_req_info {scalar_t__ num_done_req; } ;
struct tcp_req_done_item {struct tcp_req_done_item* buf; int /*<<< orphan*/  len; } ;

/* Variables and functions */
 int /*<<< orphan*/  free (struct tcp_req_done_item*) ; 
 struct tcp_req_done_item* tcp_req_info_pop_done (struct tcp_req_info*) ; 
 int /*<<< orphan*/  tcp_req_info_start_write_buf (struct tcp_req_info*,struct tcp_req_done_item*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
tcp_req_pickup_next_result(struct tcp_req_info* req)
{
	if(req->num_done_req > 0) {
		/* unlist the done item from the list of pending results */
		struct tcp_req_done_item* item = tcp_req_info_pop_done(req);
		tcp_req_info_start_write_buf(req, item->buf, item->len);
		free(item->buf);
		free(item);
	}
}