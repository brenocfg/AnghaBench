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
typedef  int /*<<< orphan*/  u8 ;
struct rv_jit_context {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  emit (int /*<<< orphan*/ ,struct rv_jit_context*) ; 
 int /*<<< orphan*/  rv_slli (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  rv_srli (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void emit_zext_32(u8 reg, struct rv_jit_context *ctx)
{
	emit(rv_slli(reg, reg, 32), ctx);
	emit(rv_srli(reg, reg, 32), ctx);
}