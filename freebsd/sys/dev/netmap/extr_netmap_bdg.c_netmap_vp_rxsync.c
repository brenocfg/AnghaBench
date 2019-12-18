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
struct netmap_kring {int /*<<< orphan*/  q_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 
 int netmap_vp_rxsync_locked (struct netmap_kring*,int) ; 

int
netmap_vp_rxsync(struct netmap_kring *kring, int flags)
{
	int n;

	mtx_lock(&kring->q_lock);
	n = netmap_vp_rxsync_locked(kring, flags);
	mtx_unlock(&kring->q_lock);
	return n;
}