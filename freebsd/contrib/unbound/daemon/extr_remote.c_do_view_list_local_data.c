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
struct worker {TYPE_1__* daemon; } ;
struct view {int /*<<< orphan*/  lock; scalar_t__ local_zones; } ;
struct TYPE_2__ {int /*<<< orphan*/  views; } ;
typedef  int /*<<< orphan*/  RES ;

/* Variables and functions */
 int /*<<< orphan*/  do_list_local_data (int /*<<< orphan*/ *,struct worker*,scalar_t__) ; 
 int /*<<< orphan*/  lock_rw_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ssl_printf (int /*<<< orphan*/ *,char*,char*) ; 
 struct view* views_find_view (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
do_view_list_local_data(RES* ssl, struct worker* worker, char* arg)
{
	struct view* v = views_find_view(worker->daemon->views,
		arg, 0 /* get read lock*/);
	if(!v) {
		ssl_printf(ssl,"no view with name: %s\n", arg);
		return;
	}
	if(v->local_zones) {
		do_list_local_data(ssl, worker, v->local_zones);
	}
	lock_rw_unlock(&v->lock);
}