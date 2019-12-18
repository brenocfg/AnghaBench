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
struct jit_ctx {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARM_COND_AL ; 
 int /*<<< orphan*/  _emit (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct jit_ctx*) ; 

__attribute__((used)) static inline void emit(u32 inst, struct jit_ctx *ctx)
{
	_emit(ARM_COND_AL, inst, ctx);
}