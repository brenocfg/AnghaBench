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
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int /*<<< orphan*/  probability ;
struct TYPE_3__ {size_t count; int /*<<< orphan*/ ** probs; int /*<<< orphan*/ * symbols; } ;
typedef  TYPE_1__ lzma_range_encoder ;

/* Variables and functions */

__attribute__((used)) static inline void
rc_bit(lzma_range_encoder *rc, probability *prob, uint32_t bit)
{
	rc->symbols[rc->count] = bit;
	rc->probs[rc->count] = prob;
	++rc->count;
}