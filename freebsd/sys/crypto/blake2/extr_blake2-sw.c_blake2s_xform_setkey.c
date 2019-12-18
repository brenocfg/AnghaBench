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
typedef  int uint16_t ;
struct blake2s_xform_ctx {int klen; int /*<<< orphan*/  key; } ;

/* Variables and functions */
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/  const*,int) ; 
 int /*<<< orphan*/  panic (char*,unsigned int) ; 

__attribute__((used)) static void
blake2s_xform_setkey(void *vctx, const uint8_t *key, uint16_t klen)
{
	struct blake2s_xform_ctx *ctx = vctx;

	if (klen > sizeof(ctx->key))
		panic("invalid klen %u", (unsigned)klen);
	memcpy(ctx->key, key, klen);
	ctx->klen = klen;
}