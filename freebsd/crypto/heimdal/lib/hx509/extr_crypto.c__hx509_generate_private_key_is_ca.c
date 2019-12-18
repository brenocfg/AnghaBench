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
struct hx509_generate_private_context {int isCA; } ;
typedef  int /*<<< orphan*/  hx509_context ;

/* Variables and functions */

int
_hx509_generate_private_key_is_ca(hx509_context context,
				  struct hx509_generate_private_context *ctx)
{
    ctx->isCA = 1;
    return 0;
}