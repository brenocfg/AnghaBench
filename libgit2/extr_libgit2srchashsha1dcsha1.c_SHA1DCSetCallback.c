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
typedef  int /*<<< orphan*/  collision_block_callback ;
struct TYPE_3__ {int /*<<< orphan*/  callback; } ;
typedef  TYPE_1__ SHA1_CTX ;

/* Variables and functions */

void SHA1DCSetCallback(SHA1_CTX* ctx, collision_block_callback callback)
{
	ctx->callback = callback;
}