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
struct statsblobv1 {scalar_t__ abi; } ;
struct sb_visitcb_ctx {void* usrctx; int /*<<< orphan*/ * cb; } ;
typedef  int /*<<< orphan*/ * stats_blob_visitcb_t ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ STATS_ABI_V1 ; 
 int /*<<< orphan*/  stats_v1_blob_iter (struct statsblobv1*,int /*<<< orphan*/ ,struct sb_visitcb_ctx*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stats_v1_itercb_visit ; 

int
stats_v1_blob_visit(struct statsblobv1 *sb, stats_blob_visitcb_t func,
    void *usrctx)
{
	struct sb_visitcb_ctx vctx;

	if (sb == NULL || sb->abi != STATS_ABI_V1 || func == NULL)
		return (EINVAL);

	vctx.cb = func;
	vctx.usrctx = usrctx;

	stats_v1_blob_iter(sb, stats_v1_itercb_visit, &vctx, 0);

	return (0);
}