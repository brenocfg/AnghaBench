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
struct replay_cache {size_t rc_maxsize; int /*<<< orphan*/  rc_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  replay_prune (struct replay_cache*) ; 

void
replay_setsize(struct replay_cache *rc, size_t newmaxsize)
{

	mtx_lock(&rc->rc_lock);
	rc->rc_maxsize = newmaxsize;
	replay_prune(rc);
	mtx_unlock(&rc->rc_lock);
}