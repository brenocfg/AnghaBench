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
struct TYPE_2__ {int /*<<< orphan*/  ev_base; } ;
struct event_once {TYPE_1__ ev; int /*<<< orphan*/  arg; int /*<<< orphan*/  (* cb ) (int /*<<< orphan*/ ,short,int /*<<< orphan*/ ) ;} ;
typedef  int /*<<< orphan*/  evutil_socket_t ;

/* Variables and functions */
 int /*<<< orphan*/  EVBASE_ACQUIRE_LOCK (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EVBASE_RELEASE_LOCK (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LIST_REMOVE (struct event_once*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  event_debug_unassign (TYPE_1__*) ; 
 int /*<<< orphan*/  mm_free (struct event_once*) ; 
 int /*<<< orphan*/  next_once ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,short,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  th_base_lock ; 

__attribute__((used)) static void
event_once_cb(evutil_socket_t fd, short events, void *arg)
{
	struct event_once *eonce = arg;

	(*eonce->cb)(fd, events, eonce->arg);
	EVBASE_ACQUIRE_LOCK(eonce->ev.ev_base, th_base_lock);
	LIST_REMOVE(eonce, next_once);
	EVBASE_RELEASE_LOCK(eonce->ev.ev_base, th_base_lock);
	event_debug_unassign(&eonce->ev);
	mm_free(eonce);
}