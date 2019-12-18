#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_5__ {int /*<<< orphan*/  filter; } ;
typedef  TYPE_1__ qlnx_host_t ;

/* Variables and functions */
 int /*<<< orphan*/  ECORE_ACCEPT_MCAST_UNMATCHED ; 
 int /*<<< orphan*/  ECORE_ACCEPT_UCAST_UNMATCHED ; 
 int qlnx_set_rx_accept_filter (TYPE_1__*,int /*<<< orphan*/ ) ; 
 scalar_t__ qlnx_vf_device (TYPE_1__*) ; 

__attribute__((used)) static int
qlnx_set_promisc(qlnx_host_t *ha)
{
	int	rc = 0;
	uint8_t	filter;

	if (qlnx_vf_device(ha) == 0)
		return (0);

	filter = ha->filter;
	filter |= ECORE_ACCEPT_MCAST_UNMATCHED;
	filter |= ECORE_ACCEPT_UCAST_UNMATCHED;

	rc = qlnx_set_rx_accept_filter(ha, filter);
	return (rc);
}