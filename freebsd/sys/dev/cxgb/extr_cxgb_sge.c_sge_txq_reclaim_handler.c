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
struct sge_qset {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  reclaim_completed_tx (struct sge_qset*,int,int) ; 

__attribute__((used)) static void
sge_txq_reclaim_handler(void *arg, int ncount)
{
	struct sge_qset *qs = arg;
	int i;

	for (i = 0; i < 3; i++)
		reclaim_completed_tx(qs, 16, i);
}