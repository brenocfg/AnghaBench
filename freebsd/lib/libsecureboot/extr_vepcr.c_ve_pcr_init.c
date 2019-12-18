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
struct TYPE_5__ {int /*<<< orphan*/  vtable; } ;
struct TYPE_4__ {int /*<<< orphan*/  (* init ) (int /*<<< orphan*/ *) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  br_sha256_SIZE ; 
 TYPE_1__ br_sha256_vtable ; 
 TYPE_2__ pcr_ctx ; 
 int /*<<< orphan*/  pcr_hlen ; 
 TYPE_1__* pcr_md ; 
 scalar_t__ pcr_updating ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ *) ; 

void
ve_pcr_init(void)
{
	pcr_updating = 0;
	pcr_hlen = br_sha256_SIZE;
	pcr_md = &br_sha256_vtable;
	pcr_md->init(&pcr_ctx.vtable);
}