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
 int /*<<< orphan*/  RV_REG_T2 ; 
 int /*<<< orphan*/  emit (int /*<<< orphan*/ ,struct rv_jit_context*) ; 
 int /*<<< orphan*/  rv_addiw (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void emit_sext_32_rd(u8 *rd, struct rv_jit_context *ctx)
{
	emit(rv_addiw(RV_REG_T2, *rd, 0), ctx);
	*rd = RV_REG_T2;
}