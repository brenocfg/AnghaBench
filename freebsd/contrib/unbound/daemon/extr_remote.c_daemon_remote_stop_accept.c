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
struct listen_list {int /*<<< orphan*/  com; struct listen_list* next; } ;
struct daemon_remote {struct listen_list* accept_list; } ;

/* Variables and functions */
 int /*<<< orphan*/  comm_point_stop_listening (int /*<<< orphan*/ ) ; 

void daemon_remote_stop_accept(struct daemon_remote* rc)
{
	struct listen_list* p;
	for(p=rc->accept_list; p; p=p->next) {
		comm_point_stop_listening(p->com);	
	}
}