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
typedef  scalar_t__ u32 ;
struct mv_cesa_engine {scalar_t__ int_mask; scalar_t__ regs; } ;

/* Variables and functions */
 scalar_t__ CESA_SA_INT_MSK ; 
 int /*<<< orphan*/  writel_relaxed (scalar_t__,scalar_t__) ; 

__attribute__((used)) static inline void mv_cesa_set_int_mask(struct mv_cesa_engine *engine,
					u32 int_mask)
{
	if (int_mask == engine->int_mask)
		return;

	writel_relaxed(int_mask, engine->regs + CESA_SA_INT_MSK);
	engine->int_mask = int_mask;
}