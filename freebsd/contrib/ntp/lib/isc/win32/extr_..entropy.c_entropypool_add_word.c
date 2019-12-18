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
typedef  int isc_uint32_t ;
struct TYPE_3__ {int* pool; int cursor; int rotate; } ;
typedef  TYPE_1__ isc_entropypool_t ;

/* Variables and functions */
 int RND_POOLWORDS ; 
 int TAP1 ; 
 int TAP2 ; 
 int TAP3 ; 
 int TAP4 ; 
 int TAP5 ; 

__attribute__((used)) static inline void
entropypool_add_word(isc_entropypool_t *rp, isc_uint32_t val) {
	/*
	 * Steal some values out of the pool, and xor them into the
	 * word we were given.
	 *
	 * Mix the new value into the pool using xor.  This will
	 * prevent the actual values from being known to the caller
	 * since the previous values are assumed to be unknown as well.
	 */
	val ^= rp->pool[(rp->cursor + TAP1) & (RND_POOLWORDS - 1)];
	val ^= rp->pool[(rp->cursor + TAP2) & (RND_POOLWORDS - 1)];
	val ^= rp->pool[(rp->cursor + TAP3) & (RND_POOLWORDS - 1)];
	val ^= rp->pool[(rp->cursor + TAP4) & (RND_POOLWORDS - 1)];
	val ^= rp->pool[(rp->cursor + TAP5) & (RND_POOLWORDS - 1)];
	if (rp->rotate == 0)
		rp->pool[rp->cursor++] ^= val;
	else
		rp->pool[rp->cursor++] ^=
		  ((val << rp->rotate) | (val >> (32 - rp->rotate)));

	/*
	 * If we have looped around the pool, increment the rotate
	 * variable so the next value will get xored in rotated to
	 * a different position.
	 * Increment by a value that is relatively prime to the word size
	 * to try to spread the bits throughout the pool quickly when the
	 * pool is empty.
	 */
	if (rp->cursor == RND_POOLWORDS) {
		rp->cursor = 0;
		rp->rotate = (rp->rotate + 7) & 31;
	}
}