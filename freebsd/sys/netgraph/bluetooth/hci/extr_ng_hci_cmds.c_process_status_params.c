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
#define  NG_HCI_OCF_GET_LINK_QUALITY 131 
#define  NG_HCI_OCF_READ_FAILED_CONTACT_CNTR 130 
#define  NG_HCI_OCF_READ_RSSI 129 
#define  NG_HCI_OCF_RESET_FAILED_CONTACT_CNTR 128 

__attribute__((used)) static int
process_status_params(ng_hci_unit_p unit, u_int16_t ocf, struct mbuf *mcp,
		struct mbuf *mrp)
{
	int	error = 0;

	switch (ocf) {
	case NG_HCI_OCF_READ_FAILED_CONTACT_CNTR:
	case NG_HCI_OCF_RESET_FAILED_CONTACT_CNTR:
	case NG_HCI_OCF_GET_LINK_QUALITY:
	case NG_HCI_OCF_READ_RSSI:
		/* These do not need post processing */
		break;

	default:
		error = EINVAL;
		break;
	}

	NG_FREE_M(mcp);
	NG_FREE_M(mrp);

	return (error);
}