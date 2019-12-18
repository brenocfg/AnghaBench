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
struct TYPE_3__ {int /*<<< orphan*/  key; int /*<<< orphan*/  md5ctx; } ;
typedef  TYPE_1__ isc_hmacmd5_t ;

/* Variables and functions */
 int /*<<< orphan*/  isc_md5_invalidate (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

void
isc_hmacmd5_invalidate(isc_hmacmd5_t *ctx) {
	isc_md5_invalidate(&ctx->md5ctx);
	memset(ctx->key, 0, sizeof(ctx->key));
}