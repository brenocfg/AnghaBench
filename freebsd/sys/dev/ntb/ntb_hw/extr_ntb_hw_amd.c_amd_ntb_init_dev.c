#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct amd_ntb_softc {unsigned long long db_valid_mask; int conn_type; int spad_count; int self_spad; int peer_spad; int /*<<< orphan*/  int_mask; int /*<<< orphan*/  hb_timer; int /*<<< orphan*/  db_mask_lock; TYPE_1__* hw_info; } ;
struct TYPE_2__ {unsigned long long db_count; } ;

/* Variables and functions */
 int /*<<< orphan*/  AMD_EVENT_INTMASK ; 
 int /*<<< orphan*/  AMD_INTMASK_OFFSET ; 
 int /*<<< orphan*/  AMD_LINK_HB_TIMEOUT ; 
 int EINVAL ; 
 int /*<<< orphan*/  MTX_SPIN ; 
#define  NTB_CONN_PRI 129 
#define  NTB_CONN_SEC 128 
 int /*<<< orphan*/  amd_link_hb ; 
 int /*<<< orphan*/  amd_ntb_printf (int /*<<< orphan*/ ,char*,int const) ; 
 int /*<<< orphan*/  amd_ntb_reg_write (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  callout_init (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  callout_reset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct amd_ntb_softc*) ; 
 int /*<<< orphan*/  mtx_init (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
amd_ntb_init_dev(struct amd_ntb_softc *ntb)
{
	ntb->db_valid_mask	 = (1ull << ntb->hw_info->db_count) - 1;
	mtx_init(&ntb->db_mask_lock, "amd ntb db bits", NULL, MTX_SPIN);

	switch (ntb->conn_type) {
	case NTB_CONN_PRI:
	case NTB_CONN_SEC:
		ntb->spad_count >>= 1;

		if (ntb->conn_type == NTB_CONN_PRI) {
			ntb->self_spad = 0;
			ntb->peer_spad = 0x20;
		} else {
			ntb->self_spad = 0x20;
			ntb->peer_spad = 0;
		}

		callout_init(&ntb->hb_timer, 1);
		callout_reset(&ntb->hb_timer, AMD_LINK_HB_TIMEOUT,
		    amd_link_hb, ntb);

		break;

	default:
		amd_ntb_printf(0, "Unsupported AMD NTB topology %d\n",
		    ntb->conn_type);
		return (EINVAL);
	}

	ntb->int_mask = AMD_EVENT_INTMASK;
	amd_ntb_reg_write(4, AMD_INTMASK_OFFSET, ntb->int_mask);

	return (0);
}