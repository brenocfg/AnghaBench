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
struct eap_peer_config {scalar_t__ identity_len; int /*<<< orphan*/ * phase1; int /*<<< orphan*/  identity; } ;

/* Variables and functions */
 int /*<<< orphan*/  WSC_ID_ENROLLEE ; 
 scalar_t__ WSC_ID_ENROLLEE_LEN ; 
 scalar_t__ os_memcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/ * os_strstr (int /*<<< orphan*/ *,char*) ; 

int eap_is_wps_pbc_enrollee(struct eap_peer_config *conf)
{
	if (conf->identity_len != WSC_ID_ENROLLEE_LEN ||
	    os_memcmp(conf->identity, WSC_ID_ENROLLEE, WSC_ID_ENROLLEE_LEN))
		return 0; /* Not a WPS Enrollee */

	if (conf->phase1 == NULL || os_strstr(conf->phase1, "pbc=1") == NULL)
		return 0; /* Not using PBC */

	return 1;
}