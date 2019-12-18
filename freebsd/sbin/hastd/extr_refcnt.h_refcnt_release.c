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
typedef  int /*<<< orphan*/  refcnt_t ;

/* Variables and functions */
 int /*<<< orphan*/  PJDLOG_ASSERT (int) ; 
 unsigned int atomic_fetchadd_int (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static __inline unsigned int
refcnt_release(refcnt_t *count)
{
	unsigned int old;

	/* XXX: Should this have a rel membar? */
	old = atomic_fetchadd_int(count, -1);
	PJDLOG_ASSERT(old > 0);
	return (old - 1);
}