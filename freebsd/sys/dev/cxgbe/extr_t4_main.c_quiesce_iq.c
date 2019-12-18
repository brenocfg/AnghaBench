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
struct sge_iq {int /*<<< orphan*/  state; } ;
struct adapter {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  IQS_DISABLED ; 
 int /*<<< orphan*/  IQS_IDLE ; 
 int /*<<< orphan*/  atomic_cmpset_int (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pause (char*,int) ; 

__attribute__((used)) static void
quiesce_iq(struct adapter *sc, struct sge_iq *iq)
{
	(void) sc;	/* unused */

	/* Synchronize with the interrupt handler */
	while (!atomic_cmpset_int(&iq->state, IQS_IDLE, IQS_DISABLED))
		pause("iqfree", 1);
}