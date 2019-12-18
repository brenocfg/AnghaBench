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
 int MA_NOTRECURSED ; 
 int MA_OWNED ; 
 int /*<<< orphan*/  mtx_assert (struct mtx*,int) ; 
 int /*<<< orphan*/  mtx_unlock (struct mtx*) ; 

uintptr_t
unlock_mtx(struct lock_object *lock)
{
	struct mtx *m;

	m = (struct mtx *)lock;
	mtx_assert(m, MA_OWNED | MA_NOTRECURSED);
	mtx_unlock(m);
	return (0);
}