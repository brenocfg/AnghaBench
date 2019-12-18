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
 int /*<<< orphan*/  nm_kr_put (struct netmap_kring*) ; 
 int /*<<< orphan*/  nm_kr_stop (struct netmap_kring*,int) ; 

__attribute__((used)) static void
netmap_disable_ring(struct netmap_kring *kr, int stopped)
{
	nm_kr_stop(kr, stopped);
	// XXX check if nm_kr_stop is sufficient
	mtx_lock(&kr->q_lock);
	mtx_unlock(&kr->q_lock);
	nm_kr_put(kr);
}