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
typedef  TYPE_1__* hx509_verify_ctx ;
typedef  int /*<<< orphan*/  hx509_context ;
struct TYPE_4__ {int /*<<< orphan*/  max_depth; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  HX509_VERIFY_MAX_DEPTH ; 
 TYPE_1__* calloc (int,int) ; 

int
hx509_verify_init_ctx(hx509_context context, hx509_verify_ctx *ctx)
{
    hx509_verify_ctx c;

    c = calloc(1, sizeof(*c));
    if (c == NULL)
	return ENOMEM;

    c->max_depth = HX509_VERIFY_MAX_DEPTH;

    *ctx = c;

    return 0;
}