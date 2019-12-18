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
struct mac_policy_conf {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  mtx_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rule_head ; 
 int /*<<< orphan*/  rule_mtx ; 
 int /*<<< orphan*/  toast_rules (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
destroy(struct mac_policy_conf *mpc)
{

	mtx_destroy(&rule_mtx);
	toast_rules(&rule_head);
}