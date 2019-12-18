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
typedef  int /*<<< orphan*/  u32 ;
struct stm32_hash_request_ctx {int /*<<< orphan*/ * hw_context; } ;
struct stm32_hash_dev {int /*<<< orphan*/  dev; } ;
struct stm32_hash_ctx {int dummy; } ;
struct ahash_request {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  HASH_CR ; 
 int /*<<< orphan*/  HASH_CSR (unsigned int) ; 
 int HASH_CSR_REGISTER_NUMBER ; 
 int /*<<< orphan*/  HASH_IMR ; 
 int /*<<< orphan*/  HASH_SR ; 
 int HASH_SR_BUSY ; 
 int /*<<< orphan*/  HASH_STR ; 
 struct stm32_hash_request_ctx* ahash_request_ctx (struct ahash_request*) ; 
 int /*<<< orphan*/  cpu_relax () ; 
 struct stm32_hash_ctx* crypto_ahash_ctx (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  crypto_ahash_reqtfm (struct ahash_request*) ; 
 int /*<<< orphan*/ * kmalloc_array (int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (void*,struct stm32_hash_request_ctx*,int) ; 
 int /*<<< orphan*/  pm_runtime_get_sync (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pm_runtime_mark_last_busy (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pm_runtime_put_autosuspend (int /*<<< orphan*/ ) ; 
 struct stm32_hash_dev* stm32_hash_find_dev (struct stm32_hash_ctx*) ; 
 int stm32_hash_read (struct stm32_hash_dev*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int stm32_hash_export(struct ahash_request *req, void *out)
{
	struct stm32_hash_request_ctx *rctx = ahash_request_ctx(req);
	struct stm32_hash_ctx *ctx = crypto_ahash_ctx(crypto_ahash_reqtfm(req));
	struct stm32_hash_dev *hdev = stm32_hash_find_dev(ctx);
	u32 *preg;
	unsigned int i;

	pm_runtime_get_sync(hdev->dev);

	while ((stm32_hash_read(hdev, HASH_SR) & HASH_SR_BUSY))
		cpu_relax();

	rctx->hw_context = kmalloc_array(3 + HASH_CSR_REGISTER_NUMBER,
					 sizeof(u32),
					 GFP_KERNEL);

	preg = rctx->hw_context;

	*preg++ = stm32_hash_read(hdev, HASH_IMR);
	*preg++ = stm32_hash_read(hdev, HASH_STR);
	*preg++ = stm32_hash_read(hdev, HASH_CR);
	for (i = 0; i < HASH_CSR_REGISTER_NUMBER; i++)
		*preg++ = stm32_hash_read(hdev, HASH_CSR(i));

	pm_runtime_mark_last_busy(hdev->dev);
	pm_runtime_put_autosuspend(hdev->dev);

	memcpy(out, rctx, sizeof(*rctx));

	return 0;
}