#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
struct TYPE_6__ {uintptr_t ctx_handle; TYPE_2__* fctx; } ;
struct nitrox_crypto_ctx {TYPE_3__ u; struct crypto_ctx_hdr* chdr; int /*<<< orphan*/  ndev; } ;
struct ctx_hdr {int dummy; } ;
struct crypto_ctx_hdr {scalar_t__ vaddr; } ;
struct crypto_aead {int dummy; } ;
struct TYPE_4__ {scalar_t__ f; } ;
struct TYPE_5__ {TYPE_1__ flags; } ;

/* Variables and functions */
 int ENODEV ; 
 int ENOMEM ; 
 struct nitrox_crypto_ctx* crypto_aead_ctx (struct crypto_aead*) ; 
 struct crypto_ctx_hdr* crypto_alloc_context (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nitrox_get_first_device () ; 
 int /*<<< orphan*/  nitrox_put_device (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int nitrox_aead_init(struct crypto_aead *aead)
{
	struct nitrox_crypto_ctx *nctx = crypto_aead_ctx(aead);
	struct crypto_ctx_hdr *chdr;

	/* get the first device */
	nctx->ndev = nitrox_get_first_device();
	if (!nctx->ndev)
		return -ENODEV;

	/* allocate nitrox crypto context */
	chdr = crypto_alloc_context(nctx->ndev);
	if (!chdr) {
		nitrox_put_device(nctx->ndev);
		return -ENOMEM;
	}
	nctx->chdr = chdr;
	nctx->u.ctx_handle = (uintptr_t)((u8 *)chdr->vaddr +
					 sizeof(struct ctx_hdr));
	nctx->u.fctx->flags.f = 0;

	return 0;
}