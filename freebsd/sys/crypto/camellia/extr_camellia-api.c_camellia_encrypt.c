#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u_char ;
struct TYPE_3__ {int /*<<< orphan*/  subkey; int /*<<< orphan*/  bits; } ;
typedef  TYPE_1__ camellia_ctx ;

/* Variables and functions */
 int /*<<< orphan*/  Camellia_EncryptBlock (int /*<<< orphan*/ ,int /*<<< orphan*/  const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void
camellia_encrypt(const camellia_ctx *ctx, const u_char *src, u_char *dst)
{

    Camellia_EncryptBlock(ctx->bits, src, ctx->subkey, dst);
}