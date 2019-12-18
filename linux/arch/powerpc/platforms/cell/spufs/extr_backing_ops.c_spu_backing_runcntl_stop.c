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
struct spu_context {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  SPU_RUNCNTL_STOP ; 
 int /*<<< orphan*/  spu_backing_runcntl_write (struct spu_context*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void spu_backing_runcntl_stop(struct spu_context *ctx)
{
	spu_backing_runcntl_write(ctx, SPU_RUNCNTL_STOP);
}