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
typedef  int uint16_t ;
struct mp_ring {int size; } ;

/* Variables and functions */
 int /*<<< orphan*/  MPASS (int) ; 

__attribute__((used)) static inline uint16_t
increment_idx(struct mp_ring *r, uint16_t idx, uint16_t n)
{
	int x = r->size - idx;

	MPASS(x > 0);
	return (x > n ? idx + n : n - x);
}