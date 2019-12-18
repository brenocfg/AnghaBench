#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct platform_device {int dummy; } ;
struct class {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  revision; int /*<<< orphan*/  minor; int /*<<< orphan*/  major; } ;
struct TYPE_3__ {int /*<<< orphan*/ * function; } ;

/* Variables and functions */
 int BSP_MAX_DEVICES ; 
 int /*<<< orphan*/  DFE_Loopback_Test () ; 
 int DSL_BSP_CB_LAST ; 
 int EIO ; 
 int /*<<< orphan*/  IFX_MEI_DMSG (char*) ; 
 int /*<<< orphan*/  IFX_MEI_EMSG (char*) ; 
 int /*<<< orphan*/  IFX_MEI_InitDevNode (int) ; 
 scalar_t__ IFX_MEI_InitDevice (int) ; 
 int /*<<< orphan*/  MEI_MAJOR ; 
 int /*<<< orphan*/  MKDEV (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  THIS_MODULE ; 
 TYPE_2__ bsp_mei_version ; 
 struct class* class_create (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  device_create (struct class*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,char*) ; 
 TYPE_1__* dsl_bsp_event_callback ; 
 int /*<<< orphan*/  pr_info (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ltq_mei_probe(struct platform_device *pdev)
{
	int i = 0;
	static struct class *dsl_class;

	pr_info("IFX MEI Version %ld.%02ld.%02ld\n", bsp_mei_version.major, bsp_mei_version.minor, bsp_mei_version.revision);

	for (i = 0; i < BSP_MAX_DEVICES; i++) {
		if (IFX_MEI_InitDevice (i) != 0) {
			IFX_MEI_EMSG("Init device fail!\n");
			return -EIO;
		}
		IFX_MEI_InitDevNode (i);
	}
		for (i = 0; i <= DSL_BSP_CB_LAST ; i++)
		dsl_bsp_event_callback[i].function = NULL;

#ifdef CONFIG_LTQ_MEI_FW_LOOPBACK
	IFX_MEI_DMSG("Start loopback test...\n");
	DFE_Loopback_Test ();
#endif
	dsl_class = class_create(THIS_MODULE, "ifx_mei");
	device_create(dsl_class, NULL, MKDEV(MEI_MAJOR, 0), NULL, "ifx_mei");
	return 0;
}