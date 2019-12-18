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
struct rv_jit_context {int /*<<< orphan*/  flags; } ;

/* Variables and functions */
#define  RV_CTX_F_SEEN_CALL 134 
#define  RV_CTX_F_SEEN_S1 133 
#define  RV_CTX_F_SEEN_S2 132 
#define  RV_CTX_F_SEEN_S3 131 
#define  RV_CTX_F_SEEN_S4 130 
#define  RV_CTX_F_SEEN_S5 129 
#define  RV_CTX_F_SEEN_S6 128 
 int test_bit (int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static bool seen_reg(int reg, struct rv_jit_context *ctx)
{
	switch (reg) {
	case RV_CTX_F_SEEN_CALL:
	case RV_CTX_F_SEEN_S1:
	case RV_CTX_F_SEEN_S2:
	case RV_CTX_F_SEEN_S3:
	case RV_CTX_F_SEEN_S4:
	case RV_CTX_F_SEEN_S5:
	case RV_CTX_F_SEEN_S6:
		return test_bit(reg, &ctx->flags);
	}
	return false;
}