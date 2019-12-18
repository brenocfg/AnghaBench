#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u32 ;
struct TYPE_2__ {scalar_t__ delay_linear; } ;
struct rdt_resource {scalar_t__ default_ctrl; TYPE_1__ membw; } ;

/* Variables and functions */
 scalar_t__ MAX_MBA_BW ; 
 int /*<<< orphan*/  pr_warn_once (char*) ; 

u32 delay_bw_map(unsigned long bw, struct rdt_resource *r)
{
	if (r->membw.delay_linear)
		return MAX_MBA_BW - bw;

	pr_warn_once("Non Linear delay-bw map not supported but queried\n");
	return r->default_ctrl;
}