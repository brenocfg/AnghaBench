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
struct TYPE_3__ {int /*<<< orphan*/ * state; scalar_t__ count; } ;
typedef  TYPE_1__ RMD160_CTX ;

/* Variables and functions */
 int /*<<< orphan*/  H0 ; 
 int /*<<< orphan*/  H1 ; 
 int /*<<< orphan*/  H2 ; 
 int /*<<< orphan*/  H3 ; 
 int /*<<< orphan*/  H4 ; 

void
RMD160Init(RMD160_CTX *ctx)
{
	ctx->count = 0;
	ctx->state[0] = H0;
	ctx->state[1] = H1;
	ctx->state[2] = H2;
	ctx->state[3] = H3;
	ctx->state[4] = H4;
}