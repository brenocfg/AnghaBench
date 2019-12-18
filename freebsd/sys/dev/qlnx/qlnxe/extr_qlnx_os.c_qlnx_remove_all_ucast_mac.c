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
struct ecore_filter_ucast {int is_rx_filter; int /*<<< orphan*/  type; int /*<<< orphan*/  opcode; } ;
struct ecore_dev {int dummy; } ;
struct TYPE_3__ {struct ecore_dev cdev; } ;
typedef  TYPE_1__ qlnx_host_t ;

/* Variables and functions */
 int /*<<< orphan*/  ECORE_FILTER_MAC ; 
 int /*<<< orphan*/  ECORE_FILTER_REPLACE ; 
 int /*<<< orphan*/  ECORE_SPQ_MODE_CB ; 
 int /*<<< orphan*/  bzero (struct ecore_filter_ucast*,int) ; 
 int ecore_filter_ucast_cmd (struct ecore_dev*,struct ecore_filter_ucast*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
qlnx_remove_all_ucast_mac(qlnx_host_t *ha)
{
	struct ecore_filter_ucast	ucast;
	struct ecore_dev		*cdev;
	int				rc;

	bzero(&ucast, sizeof(struct ecore_filter_ucast));

	ucast.opcode = ECORE_FILTER_REPLACE;
	ucast.type = ECORE_FILTER_MAC; 
	ucast.is_rx_filter = 1;

	cdev = &ha->cdev;

	rc = ecore_filter_ucast_cmd(cdev, &ucast, ECORE_SPQ_MODE_CB, NULL);

	return (rc);
}