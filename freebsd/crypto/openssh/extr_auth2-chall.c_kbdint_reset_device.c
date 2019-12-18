#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {TYPE_1__* device; int /*<<< orphan*/ * ctxt; } ;
struct TYPE_4__ {int /*<<< orphan*/  (* free_ctx ) (int /*<<< orphan*/ *) ;} ;
typedef  TYPE_2__ KbdintAuthctxt ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
kbdint_reset_device(KbdintAuthctxt *kbdintctxt)
{
	if (kbdintctxt->ctxt) {
		kbdintctxt->device->free_ctx(kbdintctxt->ctxt);
		kbdintctxt->ctxt = NULL;
	}
	kbdintctxt->device = NULL;
}