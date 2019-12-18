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
typedef  int u8 ;
struct rv_jit_context {int /*<<< orphan*/  flags; } ;

/* Variables and functions */
#define  RV_CTX_F_SEEN_S1 133 
#define  RV_CTX_F_SEEN_S2 132 
#define  RV_CTX_F_SEEN_S3 131 
#define  RV_CTX_F_SEEN_S4 130 
#define  RV_CTX_F_SEEN_S5 129 
#define  RV_CTX_F_SEEN_S6 128 
 int /*<<< orphan*/  __set_bit (int,int /*<<< orphan*/ *) ; 
 int* regmap ; 

__attribute__((used)) static u8 bpf_to_rv_reg(int bpf_reg, struct rv_jit_context *ctx)
{
	u8 reg = regmap[bpf_reg];

	switch (reg) {
	case RV_CTX_F_SEEN_S1:
	case RV_CTX_F_SEEN_S2:
	case RV_CTX_F_SEEN_S3:
	case RV_CTX_F_SEEN_S4:
	case RV_CTX_F_SEEN_S5:
	case RV_CTX_F_SEEN_S6:
		__set_bit(reg, &ctx->flags);
	}
	return reg;
}