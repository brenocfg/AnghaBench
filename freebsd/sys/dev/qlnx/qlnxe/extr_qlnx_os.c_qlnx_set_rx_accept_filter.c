#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
struct ecore_filter_accept_flags {int update_rx_mode_config; int update_tx_mode_config; int tx_accept_filter; int /*<<< orphan*/  rx_accept_filter; } ;
struct ecore_dev {int dummy; } ;
struct TYPE_3__ {struct ecore_dev cdev; } ;
typedef  TYPE_1__ qlnx_host_t ;

/* Variables and functions */
 int ECORE_ACCEPT_BCAST ; 
 int ECORE_ACCEPT_MCAST_MATCHED ; 
 int ECORE_ACCEPT_UCAST_MATCHED ; 
 int /*<<< orphan*/  ECORE_SPQ_MODE_CB ; 
 int /*<<< orphan*/  bzero (struct ecore_filter_accept_flags*,int) ; 
 int ecore_filter_accept_cmd (struct ecore_dev*,int /*<<< orphan*/ ,struct ecore_filter_accept_flags,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
qlnx_set_rx_accept_filter(qlnx_host_t *ha, uint8_t filter)
{
	struct ecore_filter_accept_flags	accept;
	int					rc = 0;
	struct ecore_dev			*cdev;

	cdev = &ha->cdev;

	bzero(&accept, sizeof(struct ecore_filter_accept_flags));

	accept.update_rx_mode_config = 1;
	accept.rx_accept_filter = filter;

	accept.update_tx_mode_config = 1;
	accept.tx_accept_filter = ECORE_ACCEPT_UCAST_MATCHED |
		ECORE_ACCEPT_MCAST_MATCHED | ECORE_ACCEPT_BCAST;

	rc = ecore_filter_accept_cmd(cdev, 0, accept, false, false,
			ECORE_SPQ_MODE_CB, NULL);

	return (rc);
}