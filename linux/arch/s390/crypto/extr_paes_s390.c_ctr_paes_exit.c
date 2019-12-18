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
struct s390_paes_ctx {int /*<<< orphan*/  kb; } ;
struct crypto_tfm {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  _free_kb_keybuf (int /*<<< orphan*/ *) ; 
 struct s390_paes_ctx* crypto_tfm_ctx (struct crypto_tfm*) ; 

__attribute__((used)) static void ctr_paes_exit(struct crypto_tfm *tfm)
{
	struct s390_paes_ctx *ctx = crypto_tfm_ctx(tfm);

	_free_kb_keybuf(&ctx->kb);
}