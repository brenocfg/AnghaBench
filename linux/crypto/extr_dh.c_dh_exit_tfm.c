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
struct dh_ctx {int dummy; } ;
struct crypto_kpp {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  dh_clear_ctx (struct dh_ctx*) ; 
 struct dh_ctx* dh_get_ctx (struct crypto_kpp*) ; 

__attribute__((used)) static void dh_exit_tfm(struct crypto_kpp *tfm)
{
	struct dh_ctx *ctx = dh_get_ctx(tfm);

	dh_clear_ctx(ctx);
}