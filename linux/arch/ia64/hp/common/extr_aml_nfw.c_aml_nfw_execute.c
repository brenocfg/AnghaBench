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
struct ia64_pdesc {void* gp; void* ip; } ;
struct ia64_nfw_context {int /*<<< orphan*/ * arg; int /*<<< orphan*/  ret; int /*<<< orphan*/  gp; int /*<<< orphan*/  ip; } ;
typedef  scalar_t__ ia64_sal_handler ;

/* Variables and functions */
 int /*<<< orphan*/  IA64_FW_CALL (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 void* virt_map (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void aml_nfw_execute(struct ia64_nfw_context *c)
{
	struct ia64_pdesc virt_entry;
	ia64_sal_handler entry;

	virt_entry.ip = virt_map(c->ip);
	virt_entry.gp = virt_map(c->gp);

	entry = (ia64_sal_handler) &virt_entry;

	IA64_FW_CALL(entry, c->ret,
		     c->arg[0], c->arg[1], c->arg[2], c->arg[3],
		     c->arg[4], c->arg[5], c->arg[6], c->arg[7]);
}