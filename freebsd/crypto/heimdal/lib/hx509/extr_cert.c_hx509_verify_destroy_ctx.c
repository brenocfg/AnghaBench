#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* hx509_verify_ctx ;
struct TYPE_5__ {int /*<<< orphan*/  revoke_ctx; int /*<<< orphan*/  trust_anchors; } ;

/* Variables and functions */
 int /*<<< orphan*/  free (TYPE_1__*) ; 
 int /*<<< orphan*/  hx509_certs_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hx509_revoke_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 

void
hx509_verify_destroy_ctx(hx509_verify_ctx ctx)
{
    if (ctx) {
	hx509_certs_free(&ctx->trust_anchors);
	hx509_revoke_free(&ctx->revoke_ctx);
	memset(ctx, 0, sizeof(*ctx));
    }
    free(ctx);
}