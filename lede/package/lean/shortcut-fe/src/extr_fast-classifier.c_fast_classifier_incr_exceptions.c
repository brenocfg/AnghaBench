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
struct fast_classifier {int /*<<< orphan*/  lock; int /*<<< orphan*/ * exceptions; } ;
typedef  size_t fast_classifier_exception_t ;

/* Variables and functions */
 struct fast_classifier __fsc ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline void fast_classifier_incr_exceptions(fast_classifier_exception_t except)
{
	struct fast_classifier *sc = &__fsc;

	spin_lock_bh(&sc->lock);
	sc->exceptions[except]++;
	spin_unlock_bh(&sc->lock);
}