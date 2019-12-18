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
typedef  int /*<<< orphan*/  u16 ;
struct eapol_sm {int /*<<< orphan*/  eap; } ;
struct eap_peer_config {int dummy; } ;

/* Variables and functions */
 int eap_peer_get_erp_info (int /*<<< orphan*/ ,struct eap_peer_config*,int /*<<< orphan*/  const**,size_t*,int /*<<< orphan*/  const**,size_t*,int /*<<< orphan*/ *,int /*<<< orphan*/  const**,size_t*) ; 

int eapol_sm_get_erp_info(struct eapol_sm *sm, struct eap_peer_config *config,
			  const u8 **username, size_t *username_len,
			  const u8 **realm, size_t *realm_len,
			  u16 *erp_next_seq_num, const u8 **rrk,
			  size_t *rrk_len)
{
#ifdef CONFIG_ERP
	if (!sm)
		return -1;
	return eap_peer_get_erp_info(sm->eap, config, username, username_len,
				     realm, realm_len, erp_next_seq_num, rrk,
				     rrk_len);
#else /* CONFIG_ERP */
	return -1;
#endif /* CONFIG_ERP */
}