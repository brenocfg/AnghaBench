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
struct ptrauth_keys {int /*<<< orphan*/  apga; int /*<<< orphan*/  apdb; int /*<<< orphan*/  apda; int /*<<< orphan*/  apib; int /*<<< orphan*/  apia; } ;
struct TYPE_2__ {struct ptrauth_keys keys_user; } ;
struct task_struct {TYPE_1__ thread; } ;

/* Variables and functions */
 int EINVAL ; 
 unsigned long PR_PAC_APDAKEY ; 
 unsigned long PR_PAC_APDBKEY ; 
 unsigned long PR_PAC_APGAKEY ; 
 unsigned long PR_PAC_APIAKEY ; 
 unsigned long PR_PAC_APIBKEY ; 
 int /*<<< orphan*/  get_random_bytes (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  ptrauth_keys_init (struct ptrauth_keys*) ; 
 int /*<<< orphan*/  ptrauth_keys_switch (struct ptrauth_keys*) ; 
 int /*<<< orphan*/  system_supports_address_auth () ; 
 int /*<<< orphan*/  system_supports_generic_auth () ; 

int ptrauth_prctl_reset_keys(struct task_struct *tsk, unsigned long arg)
{
	struct ptrauth_keys *keys = &tsk->thread.keys_user;
	unsigned long addr_key_mask = PR_PAC_APIAKEY | PR_PAC_APIBKEY |
				      PR_PAC_APDAKEY | PR_PAC_APDBKEY;
	unsigned long key_mask = addr_key_mask | PR_PAC_APGAKEY;

	if (!system_supports_address_auth() && !system_supports_generic_auth())
		return -EINVAL;

	if (!arg) {
		ptrauth_keys_init(keys);
		ptrauth_keys_switch(keys);
		return 0;
	}

	if (arg & ~key_mask)
		return -EINVAL;

	if (((arg & addr_key_mask) && !system_supports_address_auth()) ||
	    ((arg & PR_PAC_APGAKEY) && !system_supports_generic_auth()))
		return -EINVAL;

	if (arg & PR_PAC_APIAKEY)
		get_random_bytes(&keys->apia, sizeof(keys->apia));
	if (arg & PR_PAC_APIBKEY)
		get_random_bytes(&keys->apib, sizeof(keys->apib));
	if (arg & PR_PAC_APDAKEY)
		get_random_bytes(&keys->apda, sizeof(keys->apda));
	if (arg & PR_PAC_APDBKEY)
		get_random_bytes(&keys->apdb, sizeof(keys->apdb));
	if (arg & PR_PAC_APGAKEY)
		get_random_bytes(&keys->apga, sizeof(keys->apga));

	ptrauth_keys_switch(keys);

	return 0;
}