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
struct mtx {int dummy; } ;
struct lock_object {int dummy; } ;

/* Variables and functions */
 int LA_LOCKED ; 
 int LA_XLOCKED ; 
 int /*<<< orphan*/  mtx_assert (struct mtx const*,int) ; 

void
assert_mtx(const struct lock_object *lock, int what)
{

	/*
	 * Treat LA_LOCKED as if LA_XLOCKED was asserted.
	 *
	 * Some callers of lc_assert uses LA_LOCKED to indicate that either
	 * a shared lock or write lock was held, while other callers uses
	 * the more strict LA_XLOCKED (used as MA_OWNED).
	 *
	 * Mutex is the only lock class that can not be shared, as a result,
	 * we can reasonably consider the caller really intends to assert
	 * LA_XLOCKED when they are asserting LA_LOCKED on a mutex object.
	 */
	if (what & LA_LOCKED) {
		what &= ~LA_LOCKED;
		what |= LA_XLOCKED;
	}
	mtx_assert((const struct mtx *)lock, what);
}