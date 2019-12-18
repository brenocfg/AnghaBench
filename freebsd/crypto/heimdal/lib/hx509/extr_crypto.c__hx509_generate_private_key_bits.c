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
struct hx509_generate_private_context {unsigned long num_bits; } ;
typedef  int /*<<< orphan*/  hx509_context ;

/* Variables and functions */

int
_hx509_generate_private_key_bits(hx509_context context,
				 struct hx509_generate_private_context *ctx,
				 unsigned long bits)
{
    ctx->num_bits = bits;
    return 0;
}