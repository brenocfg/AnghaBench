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
struct blake2s_xform_ctx {scalar_t__ klen; int /*<<< orphan*/  state; int /*<<< orphan*/  key; } ;

/* Variables and functions */
 int /*<<< orphan*/  BLAKE2S_OUTBYTES ; 
 int blake2s_init_key_ref (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 int blake2s_init_ref (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  panic (char*) ; 

__attribute__((used)) static void
blake2s_xform_init(void *vctx)
{
	struct blake2s_xform_ctx *ctx = vctx;
	int rc;

	if (ctx->klen > 0)
		rc = blake2s_init_key_ref(&ctx->state, BLAKE2S_OUTBYTES,
		    ctx->key, ctx->klen);
	else
		rc = blake2s_init_ref(&ctx->state, BLAKE2S_OUTBYTES);
	if (rc != 0)
		panic("blake2s_init_key: invalid arguments");
}