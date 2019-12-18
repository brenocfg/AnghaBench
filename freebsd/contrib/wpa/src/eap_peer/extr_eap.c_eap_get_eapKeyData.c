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
typedef  int /*<<< orphan*/  u8 ;
struct eap_sm {size_t eapKeyDataLen; int /*<<< orphan*/  const* eapKeyData; } ;

/* Variables and functions */

const u8 * eap_get_eapKeyData(struct eap_sm *sm, size_t *len)
{
	if (sm == NULL || sm->eapKeyData == NULL) {
		*len = 0;
		return NULL;
	}

	*len = sm->eapKeyDataLen;
	return sm->eapKeyData;
}