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
typedef  scalar_t__ uint32_t ;
struct TYPE_3__ {int /*<<< orphan*/  info; } ;
typedef  TYPE_1__ ibnd_node_t ;

/* Variables and functions */
 int /*<<< orphan*/  IB_NODE_DEVID_F ; 
 scalar_t__ VTR_DEVID_SLB4018 ; 
 scalar_t__ mad_get_field (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int is_line_4700(ibnd_node_t * n)
{
	uint32_t devid = mad_get_field(n->info, 0, IB_NODE_DEVID_F);
	return (devid == VTR_DEVID_SLB4018);
}