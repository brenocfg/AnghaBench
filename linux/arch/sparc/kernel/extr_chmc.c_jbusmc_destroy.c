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
struct platform_device {int /*<<< orphan*/ * resource; } ;
struct jbusmc {int /*<<< orphan*/  regs; int /*<<< orphan*/  list; } ;

/* Variables and functions */
 int /*<<< orphan*/  JBUSMC_REGS_SIZE ; 
 int /*<<< orphan*/  kfree (struct jbusmc*) ; 
 int /*<<< orphan*/  mc_list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  of_iounmap (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void jbusmc_destroy(struct platform_device *op, struct jbusmc *p)
{
	mc_list_del(&p->list);
	of_iounmap(&op->resource[0], p->regs, JBUSMC_REGS_SIZE);
	kfree(p);
}