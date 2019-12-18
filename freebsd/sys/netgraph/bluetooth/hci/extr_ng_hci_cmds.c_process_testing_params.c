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
typedef  int u_int16_t ;
struct mbuf {int dummy; } ;
typedef  int /*<<< orphan*/  ng_hci_unit_p ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  NG_FREE_M (struct mbuf*) ; 
#define  NG_HCI_OCF_ENABLE_UNIT_UNDER_TEST 130 
#define  NG_HCI_OCF_READ_LOOPBACK_MODE 129 
#define  NG_HCI_OCF_WRITE_LOOPBACK_MODE 128 

int
process_testing_params(ng_hci_unit_p unit, u_int16_t ocf, struct mbuf *mcp,
		struct mbuf *mrp)
{
	int	error = 0;

	switch (ocf) {

	/*
	 * XXX FIXME
	 * We do not support these features at this time. However,
	 * HCI node could support this and do something smart. At least
	 * node can change unit state.
	 */
 
	case NG_HCI_OCF_READ_LOOPBACK_MODE:
	case NG_HCI_OCF_WRITE_LOOPBACK_MODE:
	case NG_HCI_OCF_ENABLE_UNIT_UNDER_TEST:
		break;

	default:
		error = EINVAL;
		break;
	}

	NG_FREE_M(mcp);
	NG_FREE_M(mrp);

	return (error);
}