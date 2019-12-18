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
struct TYPE_3__ {int* ihv; int ubc_check; int detect_coll; int /*<<< orphan*/ * callback; scalar_t__ reduced_round_coll; int /*<<< orphan*/  safe_hash; scalar_t__ found_collision; scalar_t__ total; } ;
typedef  TYPE_1__ SHA1_CTX ;

/* Variables and functions */
 int /*<<< orphan*/  SHA1DC_INIT_SAFE_HASH_DEFAULT ; 

void SHA1DCInit(SHA1_CTX* ctx)
{
	ctx->total = 0;
	ctx->ihv[0] = 0x67452301;
	ctx->ihv[1] = 0xEFCDAB89;
	ctx->ihv[2] = 0x98BADCFE;
	ctx->ihv[3] = 0x10325476;
	ctx->ihv[4] = 0xC3D2E1F0;
	ctx->found_collision = 0;
	ctx->safe_hash = SHA1DC_INIT_SAFE_HASH_DEFAULT;
	ctx->ubc_check = 1;
	ctx->detect_coll = 1;
	ctx->reduced_round_coll = 0;
	ctx->callback = NULL;
}