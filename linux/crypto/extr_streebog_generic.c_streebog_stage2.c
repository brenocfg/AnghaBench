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
struct streebog_uint512 {int dummy; } ;
struct streebog_state {int /*<<< orphan*/  Sigma; int /*<<< orphan*/  N; int /*<<< orphan*/  h; } ;
typedef  int /*<<< orphan*/  m ;

/* Variables and functions */
 struct streebog_uint512 buffer512 ; 
 int /*<<< orphan*/  memcpy (struct streebog_uint512*,int /*<<< orphan*/  const*,int) ; 
 int /*<<< orphan*/  streebog_add512 (int /*<<< orphan*/ *,struct streebog_uint512*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  streebog_g (int /*<<< orphan*/ *,int /*<<< orphan*/ *,struct streebog_uint512*) ; 

__attribute__((used)) static void streebog_stage2(struct streebog_state *ctx, const u8 *data)
{
	struct streebog_uint512 m;

	memcpy(&m, data, sizeof(m));

	streebog_g(&ctx->h, &ctx->N, &m);

	streebog_add512(&ctx->N, &buffer512, &ctx->N);
	streebog_add512(&ctx->Sigma, &m, &ctx->Sigma);
}