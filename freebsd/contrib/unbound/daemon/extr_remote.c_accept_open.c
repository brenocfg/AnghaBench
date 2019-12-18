#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct listen_list {TYPE_2__* com; struct listen_list* next; } ;
struct daemon_remote {TYPE_1__* worker; struct listen_list* accept_list; } ;
struct TYPE_4__ {int do_not_close; } ;
struct TYPE_3__ {int /*<<< orphan*/  base; } ;

/* Variables and functions */
 TYPE_2__* comm_point_create_raw (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct daemon_remote*) ; 
 int /*<<< orphan*/  log_err (char*) ; 
 scalar_t__ malloc (int) ; 
 int /*<<< orphan*/  remote_accept_callback ; 

__attribute__((used)) static int
accept_open(struct daemon_remote* rc, int fd)
{
	struct listen_list* n = (struct listen_list*)malloc(sizeof(*n));
	if(!n) {
		log_err("out of memory");
		return 0;
	}
	n->next = rc->accept_list;
	rc->accept_list = n;
	/* open commpt */
	n->com = comm_point_create_raw(rc->worker->base, fd, 0, 
		&remote_accept_callback, rc);
	if(!n->com)
		return 0;
	/* keep this port open, its fd is kept in the rc portlist */
	n->com->do_not_close = 1;
	return 1;
}