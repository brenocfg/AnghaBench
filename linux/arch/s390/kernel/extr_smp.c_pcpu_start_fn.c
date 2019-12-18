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
struct pcpu {struct lowcore* lowcore; } ;
struct lowcore {unsigned long restart_fn; unsigned long restart_data; unsigned long restart_source; int /*<<< orphan*/  nodat_stack; int /*<<< orphan*/  restart_stack; } ;

/* Variables and functions */
 int /*<<< orphan*/  SIGP_RESTART ; 
 int /*<<< orphan*/  pcpu_sigp_retry (struct pcpu*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void pcpu_start_fn(struct pcpu *pcpu, void (*func)(void *), void *data)
{
	struct lowcore *lc = pcpu->lowcore;

	lc->restart_stack = lc->nodat_stack;
	lc->restart_fn = (unsigned long) func;
	lc->restart_data = (unsigned long) data;
	lc->restart_source = -1UL;
	pcpu_sigp_retry(pcpu, SIGP_RESTART, 0);
}