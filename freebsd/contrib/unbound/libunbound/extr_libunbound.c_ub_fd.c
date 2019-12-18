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
struct ub_ctx {int /*<<< orphan*/  rr_pipe; } ;

/* Variables and functions */
 int tube_read_fd (int /*<<< orphan*/ ) ; 

int 
ub_fd(struct ub_ctx* ctx)
{
	return tube_read_fd(ctx->rr_pipe);
}