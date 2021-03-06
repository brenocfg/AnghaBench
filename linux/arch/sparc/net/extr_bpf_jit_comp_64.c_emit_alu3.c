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
typedef  int u32 ;
struct jit_ctx {int dummy; } ;

/* Variables and functions */
 int RD (int) ; 
 int RS1 (int) ; 
 int RS2 (int) ; 
 int /*<<< orphan*/  emit (int,struct jit_ctx*) ; 

__attribute__((used)) static void emit_alu3(u32 opcode, u32 a, u32 b, u32 c, struct jit_ctx *ctx)
{
	emit(opcode | RS1(a) | RS2(b) | RD(c), ctx);
}