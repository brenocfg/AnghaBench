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
struct octeon_cop2_state {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ctxzone ; 
 int /*<<< orphan*/  uma_zfree (int /*<<< orphan*/ ,struct octeon_cop2_state*) ; 

void
octeon_cop2_free_ctx(struct octeon_cop2_state *ctx)
{
	uma_zfree(ctxzone, ctx);
}