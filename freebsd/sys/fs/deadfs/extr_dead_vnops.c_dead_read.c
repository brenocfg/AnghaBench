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
struct vop_read_args {TYPE_1__* a_vp; } ;
struct TYPE_2__ {int v_vflag; } ;

/* Variables and functions */
 int EIO ; 
 int VV_ISTTY ; 

int
dead_read(struct vop_read_args *ap)
{

	/*
	 * Return EOF for tty devices, EIO for others
	 */
	if ((ap->a_vp->v_vflag & VV_ISTTY) == 0)
		return (EIO);
	return (0);
}