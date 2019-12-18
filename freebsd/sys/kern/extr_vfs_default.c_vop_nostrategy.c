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
struct vop_strategy_args {TYPE_1__* a_bp; int /*<<< orphan*/  a_vp; } ;
struct TYPE_3__ {int b_error; int /*<<< orphan*/  b_ioflags; } ;

/* Variables and functions */
 int /*<<< orphan*/  BIO_ERROR ; 
 int EOPNOTSUPP ; 
 int /*<<< orphan*/  bufdone (TYPE_1__*) ; 
 int /*<<< orphan*/  printf (char*,TYPE_1__*) ; 
 int /*<<< orphan*/  vn_printf (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int
vop_nostrategy (struct vop_strategy_args *ap)
{
	printf("No strategy for buffer at %p\n", ap->a_bp);
	vn_printf(ap->a_vp, "vnode ");
	ap->a_bp->b_ioflags |= BIO_ERROR;
	ap->a_bp->b_error = EOPNOTSUPP;
	bufdone(ap->a_bp);
	return (EOPNOTSUPP);
}