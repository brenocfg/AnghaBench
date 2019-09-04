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
typedef  int /*<<< orphan*/  uint8_t ;
struct git_hash_algo {int /*<<< orphan*/  (* final_fn ) (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ;int /*<<< orphan*/  (* update_fn ) (int /*<<< orphan*/ *,void const*,size_t) ;int /*<<< orphan*/  (* init_fn ) (int /*<<< orphan*/ *) ;} ;
typedef  int /*<<< orphan*/  git_hash_ctx ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ *,void const*,size_t) ; 
 int /*<<< orphan*/  stub3 (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline void compute_hash(const struct git_hash_algo *algo, git_hash_ctx *ctx, uint8_t *final, const void *p, size_t len)
{
	algo->init_fn(ctx);
	algo->update_fn(ctx, p, len);
	algo->final_fn(final, ctx);
}