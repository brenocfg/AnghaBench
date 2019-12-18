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
typedef  int /*<<< orphan*/  isc_result_t ;
struct TYPE_3__ {char* base; scalar_t__ seen_32; int digits; int* val; int length; int /*<<< orphan*/  target; scalar_t__ seen_end; } ;
typedef  TYPE_1__ base32_decode_ctx_t ;

/* Variables and functions */
 int /*<<< orphan*/  ISC_R_BADBASE32 ; 
 int /*<<< orphan*/  ISC_R_SUCCESS ; 
 scalar_t__ ISC_TRUE ; 
 int /*<<< orphan*/  RETERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mem_tobuffer (int /*<<< orphan*/ ,unsigned char*,int) ; 
 char* strchr (char*,int) ; 

__attribute__((used)) static inline isc_result_t
base32_decode_char(base32_decode_ctx_t *ctx, int c) {
	char *s;
	unsigned int last;

	if (ctx->seen_end)
		return (ISC_R_BADBASE32);
	if ((s = strchr(ctx->base, c)) == NULL)
		return (ISC_R_BADBASE32);
	last = s - ctx->base;
	/*
	 * Handle lower case.
	 */
	if (last > 32)
		last -= 33;
	/*
	 * Check that padding is contiguous.
	 */
	if (last != 32 && ctx->seen_32 != 0)
		return (ISC_R_BADBASE32);
	/*
	 * Check that padding starts at the right place and that
	 * bits that should be zero are.
	 * Record how many significant bytes in answer (seen_32).
	 */
	if (last == 32 && ctx->seen_32 == 0)
		switch (ctx->digits) {
		case 0:
		case 1:
			return (ISC_R_BADBASE32);
		case 2:
			if ((ctx->val[1]&0x03) != 0)
				return (ISC_R_BADBASE32);
			ctx->seen_32 = 1;
			break;
		case 3:
			return (ISC_R_BADBASE32);
		case 4:
			if ((ctx->val[3]&0x0f) != 0)
				return (ISC_R_BADBASE32);
			ctx->seen_32 = 3;
			break;
		case 5:
			if ((ctx->val[4]&0x01) != 0)
				return (ISC_R_BADBASE32);
			ctx->seen_32 = 3;
			break;
		case 6:
			return (ISC_R_BADBASE32);
		case 7:
			if ((ctx->val[6]&0x07) != 0)
				return (ISC_R_BADBASE32);
			ctx->seen_32 = 4;
			break;
		}
	/*
	 * Zero fill pad values.
	 */
	ctx->val[ctx->digits++] = (last == 32) ? 0 : last;

	if (ctx->digits == 8) {
		int n = 5;
		unsigned char buf[5];

		if (ctx->seen_32 != 0) {
			ctx->seen_end = ISC_TRUE;
			n = ctx->seen_32;
		}
		buf[0] = (ctx->val[0]<<3)|(ctx->val[1]>>2);
		buf[1] = (ctx->val[1]<<6)|(ctx->val[2]<<1)|(ctx->val[3]>>4);
		buf[2] = (ctx->val[3]<<4)|(ctx->val[4]>>1);
		buf[3] = (ctx->val[4]<<7)|(ctx->val[5]<<2)|(ctx->val[6]>>3);
		buf[4] = (ctx->val[6]<<5)|(ctx->val[7]);
		RETERR(mem_tobuffer(ctx->target, buf, n));
		if (ctx->length >= 0) {
			if (n > ctx->length)
				return (ISC_R_BADBASE32);
			else
				ctx->length -= n;
		}
		ctx->digits = 0;
	}
	return (ISC_R_SUCCESS);
}