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
struct tcp_req_info {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  free (struct tcp_req_info*) ; 
 int /*<<< orphan*/  tcp_req_info_clear (struct tcp_req_info*) ; 

void
tcp_req_info_delete(struct tcp_req_info* req)
{
	if(!req) return;
	tcp_req_info_clear(req);
	/* cp is pointer back to commpoint that owns this struct and
	 * called delete on us */
	/* spool_buffer is shared udp buffer, not deleted here */
	free(req);
}