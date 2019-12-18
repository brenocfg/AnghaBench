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
typedef  int /*<<< orphan*/  u32 ;
typedef  int /*<<< orphan*/  u16 ;

/* Variables and functions */
 int /*<<< orphan*/  FIELD_PREP (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LLI_SIZE_MASK ; 
 size_t LLI_WORD1_OFFSET ; 

__attribute__((used)) static inline void cc_lli_set_size(u32 *lli_p, u16 size)
{
	lli_p[LLI_WORD1_OFFSET] &= ~LLI_SIZE_MASK;
	lli_p[LLI_WORD1_OFFSET] |= FIELD_PREP(LLI_SIZE_MASK, size);
}