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
typedef  int /*<<< orphan*/  vop_bypass_t ;
struct vop_vector {int dummy; } ;
struct vop_generic_args {TYPE_1__* a_desc; } ;
struct TYPE_2__ {int vdesc_vop_offset; } ;

/* Variables and functions */

__attribute__((used)) static vop_bypass_t *
bp_by_off(struct vop_vector *vop, struct vop_generic_args *a)
{

	return (*(vop_bypass_t **)((char *)vop + a->a_desc->vdesc_vop_offset));
}