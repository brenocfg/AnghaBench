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
typedef  TYPE_1__* hx509_verify_ctx ;
typedef  int /*<<< orphan*/  hx509_certs ;
struct TYPE_3__ {scalar_t__ trust_anchors; } ;

/* Variables and functions */
 int /*<<< orphan*/  hx509_certs_free (scalar_t__*) ; 
 scalar_t__ hx509_certs_ref (int /*<<< orphan*/ ) ; 

void
hx509_verify_attach_anchors(hx509_verify_ctx ctx, hx509_certs set)
{
    if (ctx->trust_anchors)
	hx509_certs_free(&ctx->trust_anchors);
    ctx->trust_anchors = hx509_certs_ref(set);
}