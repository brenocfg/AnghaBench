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
struct TYPE_3__ {scalar_t__ depth; scalar_t__ tos; int too_many; int /*<<< orphan*/ * bn; } ;
typedef  TYPE_1__ BN_CTX ;
typedef  int /*<<< orphan*/  BIGNUM ;

/* Variables and functions */
 scalar_t__ BN_CTX_NUM ; 
 scalar_t__ BN_CTX_NUM_POS ; 

BIGNUM *BN_CTX_get(BN_CTX *ctx)
	{
	if (ctx->depth > BN_CTX_NUM_POS || ctx->tos >= BN_CTX_NUM)
		{
		if (!ctx->too_many)
			{
			/* disable error code until BN_CTX_end is called: */
			ctx->too_many = 1;
			}
		return NULL;
		}
	return (&(ctx->bn[ctx->tos++]));
	}