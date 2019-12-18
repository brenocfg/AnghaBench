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
typedef  int /*<<< orphan*/  X509_STORE_CTX_verify_fn ;
struct TYPE_3__ {int /*<<< orphan*/  verify; } ;
typedef  TYPE_1__ X509_STORE_CTX ;

/* Variables and functions */

void X509_STORE_CTX_set_verify(X509_STORE_CTX *ctx,
                               X509_STORE_CTX_verify_fn verify)
{
    ctx->verify = verify;
}