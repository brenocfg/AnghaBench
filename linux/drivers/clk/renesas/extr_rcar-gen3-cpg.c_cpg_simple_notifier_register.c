#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct raw_notifier_head {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  notifier_call; } ;
struct cpg_simple_notifier {TYPE_1__ nb; } ;

/* Variables and functions */
 int /*<<< orphan*/  cpg_simple_notifier_call ; 
 int /*<<< orphan*/  raw_notifier_chain_register (struct raw_notifier_head*,TYPE_1__*) ; 

__attribute__((used)) static void cpg_simple_notifier_register(struct raw_notifier_head *notifiers,
					 struct cpg_simple_notifier *csn)
{
	csn->nb.notifier_call = cpg_simple_notifier_call;
	raw_notifier_chain_register(notifiers, &csn->nb);
}