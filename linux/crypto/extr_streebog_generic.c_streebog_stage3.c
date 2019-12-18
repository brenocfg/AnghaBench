#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  member_0; } ;
struct streebog_uint512 {int /*<<< orphan*/ * qword; TYPE_1__ member_0; } ;
struct streebog_state {int fillsize; int /*<<< orphan*/  h; int /*<<< orphan*/  hash; struct streebog_uint512 Sigma; struct streebog_uint512 N; struct streebog_uint512 m; } ;

/* Variables and functions */
 struct streebog_uint512 buffer0 ; 
 int /*<<< orphan*/  cpu_to_le64 (int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  streebog_add512 (struct streebog_uint512*,struct streebog_uint512*,struct streebog_uint512*) ; 
 int /*<<< orphan*/  streebog_g (int /*<<< orphan*/ *,struct streebog_uint512*,struct streebog_uint512*) ; 
 int /*<<< orphan*/  streebog_pad (struct streebog_state*) ; 

__attribute__((used)) static void streebog_stage3(struct streebog_state *ctx)
{
	struct streebog_uint512 buf = { { 0 } };

	buf.qword[0] = cpu_to_le64(ctx->fillsize << 3);
	streebog_pad(ctx);

	streebog_g(&ctx->h, &ctx->N, &ctx->m);
	streebog_add512(&ctx->N, &buf, &ctx->N);
	streebog_add512(&ctx->Sigma, &ctx->m, &ctx->Sigma);
	streebog_g(&ctx->h, &buffer0, &ctx->N);
	streebog_g(&ctx->h, &buffer0, &ctx->Sigma);
	memcpy(&ctx->hash, &ctx->h, sizeof(struct streebog_uint512));
}