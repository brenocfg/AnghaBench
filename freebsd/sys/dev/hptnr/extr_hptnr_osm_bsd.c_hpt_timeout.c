#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  priv; } ;
struct TYPE_5__ {TYPE_1__* vbus_ext; } ;
struct TYPE_4__ {scalar_t__ vbus; } ;
typedef  int /*<<< orphan*/  PVBUS ;
typedef  TYPE_2__* POS_CMDEXT ;
typedef  TYPE_3__* PCOMMAND ;

/* Variables and functions */
 int /*<<< orphan*/  KdPrint (char*) ; 
 int /*<<< orphan*/  ldm_reset_vbus (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void hpt_timeout(void *arg)
{
	PCOMMAND pCmd = (PCOMMAND)arg;
	POS_CMDEXT ext = (POS_CMDEXT)pCmd->priv;
	
	KdPrint(("pCmd %p timeout", pCmd));
	
	ldm_reset_vbus((PVBUS)ext->vbus_ext->vbus);
}