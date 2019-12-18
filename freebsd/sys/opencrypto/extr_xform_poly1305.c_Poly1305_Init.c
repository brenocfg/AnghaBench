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
struct poly1305_xform_ctx {int dummy; } ;

/* Variables and functions */

void
Poly1305_Init(struct poly1305_xform_ctx *polyctx)
{
	/* Nop */
}