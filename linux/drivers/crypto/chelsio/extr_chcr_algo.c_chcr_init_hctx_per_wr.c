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
struct chcr_hctx_per_wr {int dummy; } ;
struct chcr_ahash_req_ctx {int /*<<< orphan*/  hctx_wr; } ;

/* Variables and functions */
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static inline void chcr_init_hctx_per_wr(struct chcr_ahash_req_ctx *reqctx)
{
	memset(&reqctx->hctx_wr, 0, sizeof(struct chcr_hctx_per_wr));
}