#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_3__* hx509_revoke_ctx ;
typedef  int /*<<< orphan*/  hx509_context ;
struct TYPE_6__ {int /*<<< orphan*/ * val; scalar_t__ len; } ;
struct TYPE_7__ {int /*<<< orphan*/ * val; scalar_t__ len; } ;
struct TYPE_8__ {int ref; TYPE_1__ ocsps; TYPE_2__ crls; } ;

/* Variables and functions */
 int ENOMEM ; 
 TYPE_3__* calloc (int,int) ; 

int
hx509_revoke_init(hx509_context context, hx509_revoke_ctx *ctx)
{
    *ctx = calloc(1, sizeof(**ctx));
    if (*ctx == NULL)
	return ENOMEM;

    (*ctx)->ref = 1;
    (*ctx)->crls.len = 0;
    (*ctx)->crls.val = NULL;
    (*ctx)->ocsps.len = 0;
    (*ctx)->ocsps.val = NULL;

    return 0;
}