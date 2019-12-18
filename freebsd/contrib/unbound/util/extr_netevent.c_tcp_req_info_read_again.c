#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct comm_point {int /*<<< orphan*/  cb_arg; int /*<<< orphan*/  (* callback ) (struct comm_point*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ;int /*<<< orphan*/  tcp_do_close; scalar_t__ tcp_is_reading; TYPE_1__* tcp_req_info; } ;
struct TYPE_2__ {scalar_t__ read_again; } ;

/* Variables and functions */
 int /*<<< orphan*/  NETEVENT_CLOSED ; 
 int comm_point_tcp_handle_read (int,struct comm_point*,int /*<<< orphan*/ ) ; 
 int comm_point_tcp_handle_write (int,struct comm_point*) ; 
 int /*<<< orphan*/  fptr_ok (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fptr_whitelist_comm_point (int /*<<< orphan*/  (*) (struct comm_point*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *)) ; 
 int /*<<< orphan*/  reclaim_tcp_handler (struct comm_point*) ; 
 int /*<<< orphan*/  stub1 (struct comm_point*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
tcp_req_info_read_again(int fd, struct comm_point* c)
{
	while(c->tcp_req_info->read_again) {
		int r;
		c->tcp_req_info->read_again = 0;
		if(c->tcp_is_reading)
			r = comm_point_tcp_handle_read(fd, c, 0);
		else 	r = comm_point_tcp_handle_write(fd, c);
		if(!r) {
			reclaim_tcp_handler(c);
			if(!c->tcp_do_close) {
				fptr_ok(fptr_whitelist_comm_point(
					c->callback));
				(void)(*c->callback)(c, c->cb_arg, 
					NETEVENT_CLOSED, NULL);
			}
			return;
		}
	}
}