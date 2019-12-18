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
struct TYPE_3__ {int /*<<< orphan*/ * locks; } ;
typedef  TYPE_1__ rrmlock_t ;
typedef  scalar_t__ krw_t ;
typedef  int /*<<< orphan*/  boolean_t ;

/* Variables and functions */
 size_t RRM_TD_LOCK () ; 
 scalar_t__ RW_WRITER ; 
 int /*<<< orphan*/  rrw_held (int /*<<< orphan*/ *,scalar_t__) ; 

boolean_t
rrm_held(rrmlock_t *rrl, krw_t rw)
{
	if (rw == RW_WRITER) {
		return (rrw_held(&rrl->locks[0], rw));
	} else {
		return (rrw_held(&rrl->locks[RRM_TD_LOCK()], rw));
	}
}