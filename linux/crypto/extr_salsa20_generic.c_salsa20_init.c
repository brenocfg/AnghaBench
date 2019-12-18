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
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u32 ;
struct salsa20_ctx {int /*<<< orphan*/  initial_state; } ;

/* Variables and functions */
 int /*<<< orphan*/  get_unaligned_le32 (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void salsa20_init(u32 *state, const struct salsa20_ctx *ctx,
			 const u8 *iv)
{
	memcpy(state, ctx->initial_state, sizeof(ctx->initial_state));
	state[6] = get_unaligned_le32(iv + 0);
	state[7] = get_unaligned_le32(iv + 4);
}