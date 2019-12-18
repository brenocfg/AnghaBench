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
struct netfront_info {int num_queues; int /*<<< orphan*/ * rxq; } ;

/* Variables and functions */
 int /*<<< orphan*/  M_DEVBUF ; 
 int /*<<< orphan*/  destroy_rxq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
destroy_rxqs(struct netfront_info *np)
{
	int i;

	for (i = 0; i < np->num_queues; i++)
		destroy_rxq(&np->rxq[i]);

	free(np->rxq, M_DEVBUF);
	np->rxq = NULL;
}