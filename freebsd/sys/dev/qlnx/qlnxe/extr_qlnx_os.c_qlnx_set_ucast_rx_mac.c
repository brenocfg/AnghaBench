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
struct ecore_filter_ucast {int opcode; int is_rx_filter; int /*<<< orphan*/ * mac; scalar_t__ vport_to_add_to; int /*<<< orphan*/  type; } ;
struct ecore_dev {int dummy; } ;
struct TYPE_3__ {struct ecore_dev cdev; } ;
typedef  TYPE_1__ qlnx_host_t ;
typedef  enum ecore_filter_opcode { ____Placeholder_ecore_filter_opcode } ecore_filter_opcode ;

/* Variables and functions */
 int /*<<< orphan*/  ECORE_FILTER_MAC ; 
 int /*<<< orphan*/  ECORE_SPQ_MODE_CB ; 
 int /*<<< orphan*/  ETH_ALEN ; 
 int /*<<< orphan*/  bzero (struct ecore_filter_ucast*,int) ; 
 int ecore_filter_ucast_cmd (struct ecore_dev*,struct ecore_filter_ucast*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,unsigned char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
qlnx_set_ucast_rx_mac(qlnx_host_t *ha,
	enum ecore_filter_opcode opcode,
	unsigned char mac[ETH_ALEN])
{
	struct ecore_filter_ucast	ucast;
	struct ecore_dev		*cdev;
	int				rc;

	cdev = &ha->cdev;

	bzero(&ucast, sizeof(struct ecore_filter_ucast));

        ucast.opcode = opcode;
        ucast.type = ECORE_FILTER_MAC;
        ucast.is_rx_filter = 1;
        ucast.vport_to_add_to = 0;
        memcpy(&ucast.mac[0], mac, ETH_ALEN);

	rc = ecore_filter_ucast_cmd(cdev, &ucast, ECORE_SPQ_MODE_CB, NULL);

        return (rc);
}