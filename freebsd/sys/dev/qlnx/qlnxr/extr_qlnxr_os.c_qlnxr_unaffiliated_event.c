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
typedef  int /*<<< orphan*/  u8 ;
struct qlnxr_dev {int /*<<< orphan*/ * ha; } ;
typedef  int /*<<< orphan*/  qlnx_host_t ;

/* Variables and functions */
 int /*<<< orphan*/  QL_DPRINT12 (int /*<<< orphan*/ *,char*) ; 

void
qlnxr_unaffiliated_event(void *context, u8 e_code)
{
        struct qlnxr_dev *dev = (struct qlnxr_dev *)context;
	qlnx_host_t *ha;

	ha = dev->ha;

	QL_DPRINT12(ha, "enter/exit \n");
	return;
}