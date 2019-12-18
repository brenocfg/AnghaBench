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
struct vop_is_text_args {TYPE_1__* a_vp; } ;
struct TYPE_2__ {scalar_t__ v_writecount; } ;

/* Variables and functions */

__attribute__((used)) static int
vop_stdis_text(struct vop_is_text_args *ap)
{

	return (ap->a_vp->v_writecount < 0);
}