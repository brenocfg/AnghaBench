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
struct replay_cache {int /*<<< orphan*/  rc_lock; int /*<<< orphan*/  rc_all; } ;

/* Variables and functions */
 int /*<<< orphan*/  M_RPC ; 
 scalar_t__ TAILQ_FIRST (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free (struct replay_cache*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtx_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  replay_free (struct replay_cache*,scalar_t__) ; 

void
replay_freecache(struct replay_cache *rc)
{

	mtx_lock(&rc->rc_lock);
	while (TAILQ_FIRST(&rc->rc_all))
		replay_free(rc, TAILQ_FIRST(&rc->rc_all));
	mtx_destroy(&rc->rc_lock);
	free(rc, M_RPC);
}