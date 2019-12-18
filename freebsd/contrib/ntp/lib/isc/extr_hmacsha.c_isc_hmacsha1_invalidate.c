#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  sha1ctx; } ;
typedef  TYPE_1__ isc_hmacsha1_t ;

/* Variables and functions */
 int /*<<< orphan*/  isc_sha1_invalidate (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 

void
isc_hmacsha1_invalidate(isc_hmacsha1_t *ctx) {
	isc_sha1_invalidate(&ctx->sha1ctx);
	memset(ctx, 0, sizeof(*ctx));
}