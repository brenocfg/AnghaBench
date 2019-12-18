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
typedef  int /*<<< orphan*/  time_t ;
struct TYPE_3__ {int /*<<< orphan*/  param; } ;
typedef  TYPE_1__ X509_STORE_CTX ;

/* Variables and functions */
 int /*<<< orphan*/  X509_VERIFY_PARAM_set_time (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void X509_STORE_CTX_set_time(X509_STORE_CTX *ctx, unsigned long flags,
                             time_t t)
{
    X509_VERIFY_PARAM_set_time(ctx->param, t);
}