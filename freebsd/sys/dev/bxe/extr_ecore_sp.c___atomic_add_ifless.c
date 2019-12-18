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
typedef  int /*<<< orphan*/  ecore_atomic_t ;

/* Variables and functions */
 int ECORE_ATOMIC_CMPXCHG (int /*<<< orphan*/ *,int,int) ; 
 int ECORE_ATOMIC_READ (int /*<<< orphan*/ *) ; 
 scalar_t__ ECORE_LIKELY (int) ; 
 scalar_t__ ECORE_UNLIKELY (int) ; 
 int FALSE ; 
 int TRUE ; 

__attribute__((used)) static inline bool __atomic_add_ifless(ecore_atomic_t *v, int a, int u)
{
	int c, old;

	c = ECORE_ATOMIC_READ(v);
	for (;;) {
		if (ECORE_UNLIKELY(c + a >= u))
			return FALSE;

		old = ECORE_ATOMIC_CMPXCHG((v), c, c + a);
		if (ECORE_LIKELY(old == c))
			break;
		c = old;
	}

	return TRUE;
}