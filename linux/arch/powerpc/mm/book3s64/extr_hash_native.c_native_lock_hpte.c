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
struct hash_pte {int /*<<< orphan*/  v; } ;

/* Variables and functions */
 int /*<<< orphan*/  HPTE_LOCK_BIT ; 
 int /*<<< orphan*/  spin_begin () ; 
 int /*<<< orphan*/  spin_cpu_relax () ; 
 int /*<<< orphan*/  spin_end () ; 
 int /*<<< orphan*/  test_and_set_bit_lock (int /*<<< orphan*/ ,unsigned long*) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,unsigned long*) ; 

__attribute__((used)) static inline void native_lock_hpte(struct hash_pte *hptep)
{
	unsigned long *word = (unsigned long *)&hptep->v;

	while (1) {
		if (!test_and_set_bit_lock(HPTE_LOCK_BIT, word))
			break;
		spin_begin();
		while(test_bit(HPTE_LOCK_BIT, word))
			spin_cpu_relax();
		spin_end();
	}
}