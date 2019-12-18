#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/ * hx509_validate_ctx ;
typedef  int /*<<< orphan*/  hx509_context ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/ * malloc (int) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

int
hx509_validate_ctx_init(hx509_context context, hx509_validate_ctx *ctx)
{
    *ctx = malloc(sizeof(**ctx));
    if (*ctx == NULL)
	return ENOMEM;
    memset(*ctx, 0, sizeof(**ctx));
    return 0;
}