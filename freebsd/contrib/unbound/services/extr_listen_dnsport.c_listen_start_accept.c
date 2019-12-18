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
struct listen_list {TYPE_1__* com; struct listen_list* next; } ;
struct listen_dnsport {struct listen_list* cps; } ;
struct TYPE_2__ {scalar_t__ type; int /*<<< orphan*/ * tcp_free; } ;

/* Variables and functions */
 int /*<<< orphan*/  comm_point_start_listening (TYPE_1__*,int,int) ; 
 scalar_t__ comm_tcp_accept ; 

void listen_start_accept(struct listen_dnsport* listen)
{
	/* do not start the ones that have no tcp_free list, it is no
	 * use to listen to them because they have no free tcp handlers */
	struct listen_list* p;
	for(p=listen->cps; p; p=p->next) {
		if(p->com->type == comm_tcp_accept &&
			p->com->tcp_free != NULL) {
			comm_point_start_listening(p->com, -1, -1);
		}
	}
}