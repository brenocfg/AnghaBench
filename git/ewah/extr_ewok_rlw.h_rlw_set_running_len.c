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
typedef  int eword_t ;

/* Variables and functions */
 int RLW_LARGEST_RUNNING_COUNT_SHIFT ; 

__attribute__((used)) static inline void rlw_set_running_len(eword_t *word, eword_t l)
{
	*word |= RLW_LARGEST_RUNNING_COUNT_SHIFT;
	*word &= (l << 1) | (~RLW_LARGEST_RUNNING_COUNT_SHIFT);
}