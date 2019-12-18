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
struct sshmac {int type; int /*<<< orphan*/ * key; int /*<<< orphan*/ * umac_ctx; int /*<<< orphan*/  key_len; int /*<<< orphan*/ * hmac_ctx; } ;

/* Variables and functions */
#define  SSH_DIGEST 130 
 int SSH_ERR_ALLOC_FAIL ; 
 int SSH_ERR_INVALID_ARGUMENT ; 
#define  SSH_UMAC 129 
#define  SSH_UMAC128 128 
 int /*<<< orphan*/  ssh_hmac_init (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * umac128_new (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * umac_new (int /*<<< orphan*/ *) ; 

int
mac_init(struct sshmac *mac)
{
	if (mac->key == NULL)
		return SSH_ERR_INVALID_ARGUMENT;
	switch (mac->type) {
	case SSH_DIGEST:
		if (mac->hmac_ctx == NULL ||
		    ssh_hmac_init(mac->hmac_ctx, mac->key, mac->key_len) < 0)
			return SSH_ERR_INVALID_ARGUMENT;
		return 0;
	case SSH_UMAC:
		if ((mac->umac_ctx = umac_new(mac->key)) == NULL)
			return SSH_ERR_ALLOC_FAIL;
		return 0;
	case SSH_UMAC128:
		if ((mac->umac_ctx = umac128_new(mac->key)) == NULL)
			return SSH_ERR_ALLOC_FAIL;
		return 0;
	default:
		return SSH_ERR_INVALID_ARGUMENT;
	}
}