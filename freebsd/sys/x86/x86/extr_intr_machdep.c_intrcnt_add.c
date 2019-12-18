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
typedef  int /*<<< orphan*/  u_long ;

/* Variables and functions */
 int /*<<< orphan*/  MPASS (int) ; 
 int /*<<< orphan*/ * intrcnt ; 
 size_t intrcnt_index ; 
 int /*<<< orphan*/  intrcnt_lock ; 
 int /*<<< orphan*/  intrcnt_setname (char const*,size_t) ; 
 int /*<<< orphan*/  mtx_lock_spin (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock_spin (int /*<<< orphan*/ *) ; 
 size_t nintrcnt ; 

void
intrcnt_add(const char *name, u_long **countp)
{

	mtx_lock_spin(&intrcnt_lock);
	MPASS(intrcnt_index < nintrcnt);
	*countp = &intrcnt[intrcnt_index];
	intrcnt_setname(name, intrcnt_index);
	intrcnt_index++;
	mtx_unlock_spin(&intrcnt_lock);
}