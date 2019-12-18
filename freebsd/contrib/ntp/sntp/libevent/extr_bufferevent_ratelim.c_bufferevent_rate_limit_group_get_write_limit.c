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
struct TYPE_2__ {int /*<<< orphan*/  write_limit; } ;
struct bufferevent_rate_limit_group {TYPE_1__ rate_limit; } ;
typedef  int /*<<< orphan*/  ev_ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  LOCK_GROUP (struct bufferevent_rate_limit_group*) ; 
 int /*<<< orphan*/  UNLOCK_GROUP (struct bufferevent_rate_limit_group*) ; 

ev_ssize_t
bufferevent_rate_limit_group_get_write_limit(
	struct bufferevent_rate_limit_group *grp)
{
	ev_ssize_t r;
	LOCK_GROUP(grp);
	r = grp->rate_limit.write_limit;
	UNLOCK_GROUP(grp);
	return r;
}