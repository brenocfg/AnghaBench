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
typedef  int /*<<< orphan*/  u16 ;
struct eapol_sm {int /*<<< orphan*/  eap; } ;

/* Variables and functions */
 int eap_peer_update_erp_next_seq_num (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int eapol_sm_update_erp_next_seq_num(struct eapol_sm *sm, u16 next_seq_num)
{
#ifdef CONFIG_ERP
	if (!sm)
		return -1;
	return eap_peer_update_erp_next_seq_num(sm->eap, next_seq_num);
#else /* CONFIG_ERP */
	return -1;
#endif /* CONFIG_ERP */
}