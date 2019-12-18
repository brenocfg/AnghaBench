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
struct tool_mw {size_t size; int /*<<< orphan*/  widx; int /*<<< orphan*/  pidx; struct tool_ctx* tc; } ;
struct tool_ctx {int dummy; } ;
struct sysctl_req {int dummy; } ;
struct sysctl_oid {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  tool_free_mw (struct tool_ctx*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int tool_setup_mw (struct tool_ctx*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,size_t) ; 

__attribute__((used)) static int
tool_mw_trans_write(struct sysctl_oid *oidp, struct sysctl_req *req,
    struct tool_mw *inmw, size_t wsize)
{
	struct tool_ctx *tc = inmw->tc;
	int rc = 0;

	if (wsize == 0)
		return (EINVAL);

	/* No need to re-setup mw */
	if (inmw->size == wsize)
		return (0);

	/* free mw dma buffer */
	if (inmw->size)
		tool_free_mw(tc, inmw->pidx, inmw->widx);

	rc = tool_setup_mw(tc, inmw->pidx, inmw->widx, wsize);

	return (rc);
}