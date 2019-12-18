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
typedef  int /*<<< orphan*/  isc_buffer_t ;
struct TYPE_3__ {int length; char const* base; int /*<<< orphan*/ * target; scalar_t__ seen_32; int /*<<< orphan*/  seen_end; scalar_t__ digits; } ;
typedef  TYPE_1__ base32_decode_ctx_t ;

/* Variables and functions */
 int /*<<< orphan*/  ISC_FALSE ; 

__attribute__((used)) static inline void
base32_decode_init(base32_decode_ctx_t *ctx, int length,
		   const char base[], isc_buffer_t *target)
{
	ctx->digits = 0;
	ctx->seen_end = ISC_FALSE;
	ctx->seen_32 = 0;
	ctx->length = length;
	ctx->target = target;
	ctx->base = base;
}