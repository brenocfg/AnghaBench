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
typedef  int /*<<< orphan*/  u64 ;
struct spu_context {int /*<<< orphan*/  object_id; } ;

/* Variables and functions */

__attribute__((used)) static u64 spufs_object_id_get(struct spu_context *ctx)
{
	/* FIXME: Should there really be no locking here? */
	return ctx->object_id;
}