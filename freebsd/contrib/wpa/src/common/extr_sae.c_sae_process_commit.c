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
typedef  int /*<<< orphan*/  u8 ;
struct sae_data {TYPE_1__* tmp; } ;
struct TYPE_2__ {scalar_t__ dh; scalar_t__ ec; } ;

/* Variables and functions */
 int SAE_MAX_PRIME_LEN ; 
 scalar_t__ sae_derive_k_ecc (struct sae_data*,int /*<<< orphan*/ *) ; 
 scalar_t__ sae_derive_k_ffc (struct sae_data*,int /*<<< orphan*/ *) ; 
 scalar_t__ sae_derive_keys (struct sae_data*,int /*<<< orphan*/ *) ; 

int sae_process_commit(struct sae_data *sae)
{
	u8 k[SAE_MAX_PRIME_LEN];
	if (sae->tmp == NULL ||
	    (sae->tmp->ec && sae_derive_k_ecc(sae, k) < 0) ||
	    (sae->tmp->dh && sae_derive_k_ffc(sae, k) < 0) ||
	    sae_derive_keys(sae, k) < 0)
		return -1;
	return 0;
}