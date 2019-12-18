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
typedef  int /*<<< orphan*/  uint32_t ;
struct netmap_kring {scalar_t__ nkr_num_slots; int /*<<< orphan*/  nr_hwtail; } ;

/* Variables and functions */
 scalar_t__ NM_ACCESS_ONCE (int /*<<< orphan*/ ) ; 
 scalar_t__ nm_prev (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static inline int
sync_kloop_norxslots(struct netmap_kring *kring, uint32_t g_head)
{
	return (NM_ACCESS_ONCE(kring->nr_hwtail) == nm_prev(g_head,
				kring->nkr_num_slots - 1));
}