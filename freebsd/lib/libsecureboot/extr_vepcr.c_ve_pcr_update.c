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
struct TYPE_4__ {int /*<<< orphan*/  vtable; } ;
struct TYPE_3__ {int /*<<< orphan*/  (* update ) (int /*<<< orphan*/ *,unsigned char*,size_t) ;} ;

/* Variables and functions */
 TYPE_2__ pcr_ctx ; 
 TYPE_1__* pcr_md ; 
 scalar_t__ pcr_updating ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ *,unsigned char*,size_t) ; 

void
ve_pcr_update(unsigned char *data, size_t dlen)
{
	if (pcr_updating != 0 && pcr_md != NULL)
		pcr_md->update(&pcr_ctx.vtable, data, dlen);
}