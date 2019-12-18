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
struct rdt_fs_context {int dummy; } ;
struct fs_context {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  kernfs_free_fs_context (struct fs_context*) ; 
 int /*<<< orphan*/  kfree (struct rdt_fs_context*) ; 
 struct rdt_fs_context* rdt_fc2context (struct fs_context*) ; 

__attribute__((used)) static void rdt_fs_context_free(struct fs_context *fc)
{
	struct rdt_fs_context *ctx = rdt_fc2context(fc);

	kernfs_free_fs_context(fc);
	kfree(ctx);
}