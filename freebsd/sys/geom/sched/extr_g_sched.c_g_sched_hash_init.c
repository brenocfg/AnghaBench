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
typedef  int /*<<< orphan*/  u_long ;
struct g_hash {int dummy; } ;
struct g_gsched {scalar_t__ gs_priv_size; } ;

/* Variables and functions */
 int /*<<< orphan*/  G_SCHED_HASH_SIZE ; 
 int /*<<< orphan*/  M_GEOM_SCHED ; 
 struct g_hash* hashinit_flags (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static struct g_hash *
g_sched_hash_init(struct g_gsched *gsp, u_long *mask, int flags)
{
	struct g_hash *hash;

	if (gsp->gs_priv_size == 0)
		return (NULL);

	hash = hashinit_flags(G_SCHED_HASH_SIZE, M_GEOM_SCHED, mask, flags);

	return (hash);
}