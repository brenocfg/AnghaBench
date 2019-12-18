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
struct eap_sm {int /*<<< orphan*/ * eapKeyData; int /*<<< orphan*/  eapKeyDataLen; } ;

/* Variables and functions */
 int /*<<< orphan*/  bin_clear_free (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void eap_sm_free_key(struct eap_sm *sm)
{
	if (sm->eapKeyData) {
		bin_clear_free(sm->eapKeyData, sm->eapKeyDataLen);
		sm->eapKeyData = NULL;
	}
}