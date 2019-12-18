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
struct sockaddr_storage {int dummy; } ;
struct outside_network {int /*<<< orphan*/  udp_buff; int /*<<< orphan*/  base; } ;
struct comm_point {int dummy; } ;
typedef  int /*<<< orphan*/  socklen_t ;
typedef  int /*<<< orphan*/  comm_point_callback_type ;

/* Variables and functions */
 int /*<<< orphan*/  close (int) ; 
 struct comm_point* comm_point_create_udp (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,void*) ; 
 int fd_for_dest (struct outside_network*,struct sockaddr_storage*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  log_err (char*) ; 

struct comm_point*
outnet_comm_point_for_udp(struct outside_network* outnet,
	comm_point_callback_type* cb, void* cb_arg,
	struct sockaddr_storage* to_addr, socklen_t to_addrlen)
{
	struct comm_point* cp;
	int fd = fd_for_dest(outnet, to_addr, to_addrlen);
	if(fd == -1) {
		return NULL;
	}
	cp = comm_point_create_udp(outnet->base, fd, outnet->udp_buff,
		cb, cb_arg);
	if(!cp) {
		log_err("malloc failure");
		close(fd);
		return NULL;
	}
	return cp;
}