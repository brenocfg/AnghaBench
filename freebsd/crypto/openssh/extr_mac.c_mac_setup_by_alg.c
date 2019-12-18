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
struct sshmac {scalar_t__ type; int key_len; int mac_len; int /*<<< orphan*/  etm; int /*<<< orphan*/ * umac_ctx; int /*<<< orphan*/ * hmac_ctx; } ;
struct macalg {scalar_t__ type; int len; int key_len; int truncatebits; int /*<<< orphan*/  etm; int /*<<< orphan*/  alg; } ;

/* Variables and functions */
 scalar_t__ SSH_DIGEST ; 
 int SSH_ERR_ALLOC_FAIL ; 
 int ssh_hmac_bytes (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * ssh_hmac_start (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
mac_setup_by_alg(struct sshmac *mac, const struct macalg *macalg)
{
	mac->type = macalg->type;
	if (mac->type == SSH_DIGEST) {
		if ((mac->hmac_ctx = ssh_hmac_start(macalg->alg)) == NULL)
			return SSH_ERR_ALLOC_FAIL;
		mac->key_len = mac->mac_len = ssh_hmac_bytes(macalg->alg);
	} else {
		mac->mac_len = macalg->len / 8;
		mac->key_len = macalg->key_len / 8;
		mac->umac_ctx = NULL;
	}
	if (macalg->truncatebits != 0)
		mac->mac_len = macalg->truncatebits / 8;
	mac->etm = macalg->etm;
	return 0;
}