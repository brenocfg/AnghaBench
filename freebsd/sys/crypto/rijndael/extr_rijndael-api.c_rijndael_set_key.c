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
struct TYPE_3__ {int /*<<< orphan*/  dk; int /*<<< orphan*/  ek; int /*<<< orphan*/  Nr; } ;
typedef  TYPE_1__ rijndael_ctx ;

/* Variables and functions */
 int /*<<< orphan*/  rijndaelKeySetupDec (int /*<<< orphan*/ ,int /*<<< orphan*/  const*,int) ; 
 int /*<<< orphan*/  rijndaelKeySetupEnc (int /*<<< orphan*/ ,int /*<<< orphan*/  const*,int) ; 

void
rijndael_set_key(rijndael_ctx *ctx, const u_char *key, int bits)
{

	ctx->Nr = rijndaelKeySetupEnc(ctx->ek, key, bits);
	rijndaelKeySetupDec(ctx->dk, key, bits);
}