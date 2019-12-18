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
struct sshmac {scalar_t__ type; int /*<<< orphan*/ * umac_ctx; int /*<<< orphan*/ * hmac_ctx; } ;

/* Variables and functions */
 scalar_t__ SSH_UMAC ; 
 scalar_t__ SSH_UMAC128 ; 
 int /*<<< orphan*/  ssh_hmac_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  umac128_delete (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  umac_delete (int /*<<< orphan*/ *) ; 

void
mac_clear(struct sshmac *mac)
{
	if (mac->type == SSH_UMAC) {
		if (mac->umac_ctx != NULL)
			umac_delete(mac->umac_ctx);
	} else if (mac->type == SSH_UMAC128) {
		if (mac->umac_ctx != NULL)
			umac128_delete(mac->umac_ctx);
	} else if (mac->hmac_ctx != NULL)
		ssh_hmac_free(mac->hmac_ctx);
	mac->hmac_ctx = NULL;
	mac->umac_ctx = NULL;
}