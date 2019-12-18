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
typedef  TYPE_1__* hx509_context ;
struct TYPE_3__ {int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  HX509_CTX_VERIFY_MISSING_OK ; 

void
hx509_context_set_missing_revoke(hx509_context context, int flag)
{
    if (flag)
	context->flags |= HX509_CTX_VERIFY_MISSING_OK;
    else
	context->flags &= ~HX509_CTX_VERIFY_MISSING_OK;
}