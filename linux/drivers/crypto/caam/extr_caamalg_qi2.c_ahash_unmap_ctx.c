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
struct device {int dummy; } ;
struct caam_hash_state {scalar_t__ ctx_dma; int /*<<< orphan*/  ctx_dma_len; } ;
struct ahash_request {int dummy; } ;
struct ahash_edesc {int dummy; } ;

/* Variables and functions */
 struct caam_hash_state* ahash_request_ctx (struct ahash_request*) ; 
 int /*<<< orphan*/  ahash_unmap (struct device*,struct ahash_edesc*,struct ahash_request*) ; 
 int /*<<< orphan*/  dma_unmap_single (struct device*,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void ahash_unmap_ctx(struct device *dev,
				   struct ahash_edesc *edesc,
				   struct ahash_request *req, u32 flag)
{
	struct caam_hash_state *state = ahash_request_ctx(req);

	if (state->ctx_dma) {
		dma_unmap_single(dev, state->ctx_dma, state->ctx_dma_len, flag);
		state->ctx_dma = 0;
	}
	ahash_unmap(dev, edesc, req);
}