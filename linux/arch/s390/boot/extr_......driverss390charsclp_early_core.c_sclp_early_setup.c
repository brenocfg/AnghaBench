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
struct init_sccb {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUILD_BUG_ON (int) ; 
 unsigned long EVTYP_MSG_MASK ; 
 unsigned long EVTYP_OPCMD_MASK ; 
 unsigned long EVTYP_VT220MSG_MASK ; 
 int PAGE_SIZE ; 
 unsigned long sccb_get_send_mask (struct init_sccb*) ; 
 int sclp_early_con_check_linemode (struct init_sccb*) ; 
 scalar_t__ sclp_early_sccb ; 
 int sclp_early_set_event_mask (struct init_sccb*,unsigned long,unsigned long) ; 

__attribute__((used)) static int sclp_early_setup(int disable, int *have_linemode, int *have_vt220)
{
	unsigned long receive_mask, send_mask;
	struct init_sccb *sccb;
	int rc;

	BUILD_BUG_ON(sizeof(struct init_sccb) > PAGE_SIZE);

	*have_linemode = *have_vt220 = 0;
	sccb = (struct init_sccb *) sclp_early_sccb;
	receive_mask = disable ? 0 : EVTYP_OPCMD_MASK;
	send_mask = disable ? 0 : EVTYP_VT220MSG_MASK | EVTYP_MSG_MASK;
	rc = sclp_early_set_event_mask(sccb, receive_mask, send_mask);
	if (rc)
		return rc;
	*have_linemode = sclp_early_con_check_linemode(sccb);
	*have_vt220 = !!(sccb_get_send_mask(sccb) & EVTYP_VT220MSG_MASK);
	return rc;
}