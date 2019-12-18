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
struct eapol_sm {int /*<<< orphan*/  eap; } ;
struct eap_hdr {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  eap_peer_finish (int /*<<< orphan*/ ,struct eap_hdr const*,size_t) ; 

void eapol_sm_process_erp_finish(struct eapol_sm *sm, const u8 *buf,
				 size_t len)
{
#ifdef CONFIG_ERP
	if (!sm)
		return;
	eap_peer_finish(sm->eap, (const struct eap_hdr *) buf, len);
#endif /* CONFIG_ERP */
}