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
struct rdt_fs_context {scalar_t__ enable_mba_mbps; scalar_t__ enable_cdpl3; scalar_t__ enable_cdpl2; } ;

/* Variables and functions */
 int cdpl2_enable () ; 
 int cdpl3_enable () ; 
 int set_mba_sc (int) ; 

__attribute__((used)) static int rdt_enable_ctx(struct rdt_fs_context *ctx)
{
	int ret = 0;

	if (ctx->enable_cdpl2)
		ret = cdpl2_enable();

	if (!ret && ctx->enable_cdpl3)
		ret = cdpl3_enable();

	if (!ret && ctx->enable_mba_mbps)
		ret = set_mba_sc(true);

	return ret;
}