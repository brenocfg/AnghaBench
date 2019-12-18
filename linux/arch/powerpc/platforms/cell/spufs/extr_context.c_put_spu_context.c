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
struct spu_context {int /*<<< orphan*/  kref; } ;

/* Variables and functions */
 int /*<<< orphan*/  destroy_spu_context ; 
 int kref_put (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

int put_spu_context(struct spu_context *ctx)
{
	return kref_put(&ctx->kref, &destroy_spu_context);
}