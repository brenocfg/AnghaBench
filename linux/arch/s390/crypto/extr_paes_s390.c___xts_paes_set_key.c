#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct s390_pxts_ctx {unsigned long fc; TYPE_1__* pk; int /*<<< orphan*/ * kb; } ;
struct TYPE_2__ {scalar_t__ type; } ;

/* Variables and functions */
 unsigned long CPACF_KM_PXTS_128 ; 
 unsigned long CPACF_KM_PXTS_256 ; 
 int EINVAL ; 
 scalar_t__ PKEY_KEYTYPE_AES_128 ; 
 scalar_t__ PKEY_KEYTYPE_AES_256 ; 
 scalar_t__ __paes_convert_key (int /*<<< orphan*/ *,TYPE_1__*) ; 
 scalar_t__ cpacf_test_func (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  km_functions ; 

__attribute__((used)) static int __xts_paes_set_key(struct s390_pxts_ctx *ctx)
{
	unsigned long fc;

	if (__paes_convert_key(&ctx->kb[0], &ctx->pk[0]) ||
	    __paes_convert_key(&ctx->kb[1], &ctx->pk[1]))
		return -EINVAL;

	if (ctx->pk[0].type != ctx->pk[1].type)
		return -EINVAL;

	/* Pick the correct function code based on the protected key type */
	fc = (ctx->pk[0].type == PKEY_KEYTYPE_AES_128) ? CPACF_KM_PXTS_128 :
		(ctx->pk[0].type == PKEY_KEYTYPE_AES_256) ?
		CPACF_KM_PXTS_256 : 0;

	/* Check if the function code is available */
	ctx->fc = (fc && cpacf_test_func(&km_functions, fc)) ? fc : 0;

	return ctx->fc ? 0 : -EINVAL;
}