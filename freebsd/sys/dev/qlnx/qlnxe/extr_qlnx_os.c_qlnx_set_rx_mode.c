#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int uint8_t ;
struct TYPE_7__ {int filter; int /*<<< orphan*/  primary_mac; } ;
typedef  TYPE_1__ qlnx_host_t ;

/* Variables and functions */
 int ECORE_ACCEPT_BCAST ; 
 int ECORE_ACCEPT_MCAST_MATCHED ; 
 int ECORE_ACCEPT_MCAST_UNMATCHED ; 
 int ECORE_ACCEPT_UCAST_MATCHED ; 
 int ECORE_ACCEPT_UCAST_UNMATCHED ; 
 int /*<<< orphan*/  ECORE_FILTER_REPLACE ; 
 int qlnx_remove_all_mcast_mac (TYPE_1__*) ; 
 int qlnx_set_rx_accept_filter (TYPE_1__*,int) ; 
 int qlnx_set_ucast_rx_mac (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ qlnx_vf_device (TYPE_1__*) ; 

__attribute__((used)) static int
qlnx_set_rx_mode(qlnx_host_t *ha)
{
	int	rc = 0;
	uint8_t	filter;

	rc = qlnx_set_ucast_rx_mac(ha, ECORE_FILTER_REPLACE, ha->primary_mac);
        if (rc)
                return rc;

	rc = qlnx_remove_all_mcast_mac(ha);
        if (rc)
                return rc;

	filter = ECORE_ACCEPT_UCAST_MATCHED |
			ECORE_ACCEPT_MCAST_MATCHED |
			ECORE_ACCEPT_BCAST;

	if (qlnx_vf_device(ha) == 0) {
		filter |= ECORE_ACCEPT_UCAST_UNMATCHED;
		filter |= ECORE_ACCEPT_MCAST_UNMATCHED;
	}
	ha->filter = filter;

	rc = qlnx_set_rx_accept_filter(ha, filter);

	return (rc);
}