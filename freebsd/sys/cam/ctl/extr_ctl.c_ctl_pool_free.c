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
struct ctl_io_pool {int /*<<< orphan*/  zone; } ;

/* Variables and functions */
 int /*<<< orphan*/  M_CTL ; 
 int /*<<< orphan*/  free (struct ctl_io_pool*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uma_zdestroy (int /*<<< orphan*/ ) ; 

void
ctl_pool_free(struct ctl_io_pool *pool)
{

	if (pool == NULL)
		return;

#ifdef IO_POOLS
	uma_zdestroy(pool->zone);
#endif
	free(pool, M_CTL);
}