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
struct s390_pxts_ctx {TYPE_1__* kb; } ;
struct crypto_tfm {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/ * key; } ;

/* Variables and functions */
 struct s390_pxts_ctx* crypto_tfm_ctx (struct crypto_tfm*) ; 

__attribute__((used)) static int xts_paes_init(struct crypto_tfm *tfm)
{
	struct s390_pxts_ctx *ctx = crypto_tfm_ctx(tfm);

	ctx->kb[0].key = NULL;
	ctx->kb[1].key = NULL;

	return 0;
}