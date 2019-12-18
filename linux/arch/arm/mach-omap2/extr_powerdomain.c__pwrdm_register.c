#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct voltagedomain {int dummy; } ;
struct TYPE_3__ {struct voltagedomain* ptr; int /*<<< orphan*/  name; } ;
struct powerdomain {scalar_t__ prcm_partition; int* state_counter; int banks; size_t state; int /*<<< orphan*/  name; scalar_t__* ret_mem_off_counter; scalar_t__ ret_logic_off_counter; int /*<<< orphan*/  node; int /*<<< orphan*/  _lock; int /*<<< orphan*/  voltdm_node; TYPE_1__ voltdm; } ;
struct TYPE_4__ {int /*<<< orphan*/  (* pwrdm_wait_transition ) (struct powerdomain*) ;int /*<<< orphan*/  (* pwrdm_has_voltdm ) () ;} ;

/* Variables and functions */
 int EEXIST ; 
 int EINVAL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 scalar_t__ OMAP4430_INVALID_PRCM_PARTITION ; 
 int PWRDM_MAX_PWRSTS ; 
 scalar_t__ _pwrdm_lookup (int /*<<< orphan*/ ) ; 
 TYPE_2__* arch_pwrdm ; 
 scalar_t__ cpu_is_omap44xx () ; 
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pr_debug (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_err (char*,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  pwrdm_list ; 
 size_t pwrdm_read_pwrst (struct powerdomain*) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 () ; 
 int /*<<< orphan*/  stub2 (struct powerdomain*) ; 
 struct voltagedomain* voltdm_lookup (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int _pwrdm_register(struct powerdomain *pwrdm)
{
	int i;
	struct voltagedomain *voltdm;

	if (!pwrdm || !pwrdm->name)
		return -EINVAL;

	if (cpu_is_omap44xx() &&
	    pwrdm->prcm_partition == OMAP4430_INVALID_PRCM_PARTITION) {
		pr_err("powerdomain: %s: missing OMAP4 PRCM partition ID\n",
		       pwrdm->name);
		return -EINVAL;
	}

	if (_pwrdm_lookup(pwrdm->name))
		return -EEXIST;

	if (arch_pwrdm && arch_pwrdm->pwrdm_has_voltdm)
		if (!arch_pwrdm->pwrdm_has_voltdm())
			goto skip_voltdm;

	voltdm = voltdm_lookup(pwrdm->voltdm.name);
	if (!voltdm) {
		pr_err("powerdomain: %s: voltagedomain %s does not exist\n",
		       pwrdm->name, pwrdm->voltdm.name);
		return -EINVAL;
	}
	pwrdm->voltdm.ptr = voltdm;
	INIT_LIST_HEAD(&pwrdm->voltdm_node);
skip_voltdm:
	spin_lock_init(&pwrdm->_lock);

	list_add(&pwrdm->node, &pwrdm_list);

	/* Initialize the powerdomain's state counter */
	for (i = 0; i < PWRDM_MAX_PWRSTS; i++)
		pwrdm->state_counter[i] = 0;

	pwrdm->ret_logic_off_counter = 0;
	for (i = 0; i < pwrdm->banks; i++)
		pwrdm->ret_mem_off_counter[i] = 0;

	if (arch_pwrdm && arch_pwrdm->pwrdm_wait_transition)
		arch_pwrdm->pwrdm_wait_transition(pwrdm);
	pwrdm->state = pwrdm_read_pwrst(pwrdm);
	pwrdm->state_counter[pwrdm->state] = 1;

	pr_debug("powerdomain: registered %s\n", pwrdm->name);

	return 0;
}