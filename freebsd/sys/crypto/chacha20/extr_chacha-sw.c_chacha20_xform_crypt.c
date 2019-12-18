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
typedef  int /*<<< orphan*/  u_int8_t ;
struct chacha_ctx {int dummy; } ;
typedef  scalar_t__ caddr_t ;

/* Variables and functions */
 int /*<<< orphan*/  chacha_encrypt_bytes (struct chacha_ctx*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void
chacha20_xform_crypt(caddr_t cctx, u_int8_t *bytes)
{
	struct chacha_ctx *ctx;

	ctx = (void *)cctx;
	chacha_encrypt_bytes(ctx, bytes, bytes, 1);
}