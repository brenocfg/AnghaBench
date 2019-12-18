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
 int /*<<< orphan*/  M_NOWAIT ; 
 int /*<<< orphan*/  ctxzone ; 
 struct octeon_cop2_state* uma_zalloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

struct octeon_cop2_state *
octeon_cop2_alloc_ctx()
{
	return uma_zalloc(ctxzone, M_NOWAIT);
}