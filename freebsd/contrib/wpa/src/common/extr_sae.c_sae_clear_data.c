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
struct sae_data {int /*<<< orphan*/  peer_commit_scalar; } ;

/* Variables and functions */
 int /*<<< orphan*/  crypto_bignum_deinit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  os_memset (struct sae_data*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  sae_clear_temp_data (struct sae_data*) ; 

void sae_clear_data(struct sae_data *sae)
{
	if (sae == NULL)
		return;
	sae_clear_temp_data(sae);
	crypto_bignum_deinit(sae->peer_commit_scalar, 0);
	os_memset(sae, 0, sizeof(*sae));
}