#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct vop_advlock_args {int /*<<< orphan*/  a_flags; int /*<<< orphan*/  a_fl; int /*<<< orphan*/  a_op; int /*<<< orphan*/  a_id; int /*<<< orphan*/  a_vp; } ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TRUE ; 
 int nlm_advlock_internal (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int
nlm_advlock(struct vop_advlock_args *ap)
{

	return (nlm_advlock_internal(ap->a_vp, ap->a_id, ap->a_op, ap->a_fl,
		ap->a_flags, FALSE, TRUE));
}