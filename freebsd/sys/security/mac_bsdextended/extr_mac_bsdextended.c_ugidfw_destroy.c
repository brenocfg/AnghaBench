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
 int MAC_BSDEXTENDED_MAXRULES ; 
 int /*<<< orphan*/  M_MACBSDEXTENDED ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtx_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ ** rules ; 
 int /*<<< orphan*/  ugidfw_mtx ; 

__attribute__((used)) static void
ugidfw_destroy(struct mac_policy_conf *mpc)
{
	int i;

	for (i = 0; i < MAC_BSDEXTENDED_MAXRULES; i++) {
		if (rules[i] != NULL)
			free(rules[i], M_MACBSDEXTENDED);
	}
	mtx_destroy(&ugidfw_mtx);
}