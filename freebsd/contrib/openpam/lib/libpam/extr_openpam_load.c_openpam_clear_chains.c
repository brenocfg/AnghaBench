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
typedef  int /*<<< orphan*/  pam_chain_t ;

/* Variables and functions */
 int PAM_NUM_FACILITIES ; 
 int /*<<< orphan*/  openpam_destroy_chain (int /*<<< orphan*/ *) ; 

void
openpam_clear_chains(pam_chain_t *policy[])
{
	int i;

	for (i = 0; i < PAM_NUM_FACILITIES; ++i) {
		openpam_destroy_chain(policy[i]);
		policy[i] = NULL;
	}
}