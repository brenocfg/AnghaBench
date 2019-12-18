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
struct sx {int dummy; } ;
struct lock_object {int dummy; } ;

/* Variables and functions */
 int SA_LOCKED ; 
 int SA_NOTRECURSED ; 
 int /*<<< orphan*/  sx_assert (struct sx*,int) ; 
 int /*<<< orphan*/  sx_sunlock (struct sx*) ; 
 scalar_t__ sx_xlocked (struct sx*) ; 
 int /*<<< orphan*/  sx_xunlock (struct sx*) ; 

uintptr_t
unlock_sx(struct lock_object *lock)
{
	struct sx *sx;

	sx = (struct sx *)lock;
	sx_assert(sx, SA_LOCKED | SA_NOTRECURSED);
	if (sx_xlocked(sx)) {
		sx_xunlock(sx);
		return (0);
	} else {
		sx_sunlock(sx);
		return (1);
	}
}