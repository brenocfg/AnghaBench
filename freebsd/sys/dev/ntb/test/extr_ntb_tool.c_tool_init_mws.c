#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct tool_mw {int widx; int pidx; int /*<<< orphan*/  addr_limit; int /*<<< orphan*/  xlat_align_size; int /*<<< orphan*/  xlat_align; int /*<<< orphan*/  phys_size; int /*<<< orphan*/  mm_base; int /*<<< orphan*/  phys_addr; int /*<<< orphan*/  mw_buf_size; int /*<<< orphan*/  mw_buf_offset; struct tool_ctx* tc; } ;
struct tool_ctx {int peer_cnt; int /*<<< orphan*/  dev; TYPE_1__* peers; } ;
struct TYPE_2__ {int inmw_cnt; struct tool_mw* inmws; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEFAULT_MW_OFF ; 
 int /*<<< orphan*/  DEFAULT_MW_SIZE ; 
 int ENOMEM ; 
 int /*<<< orphan*/  M_NTB_TOOL ; 
 int M_WAITOK ; 
 int M_ZERO ; 
 struct tool_mw* malloc (int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  memset (void*,int /*<<< orphan*/ ,int) ; 
 int ntb_mw_count (int /*<<< orphan*/ ) ; 
 int ntb_mw_get_range (int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tool_clear_mws (struct tool_ctx*) ; 

__attribute__((used)) static int
tool_init_mws(struct tool_ctx *tc)
{
	struct tool_mw *mw;
	int widx, pidx, rc;

	/* Initialize inbound memory windows and outbound MWs wrapper */
	for (pidx = 0; pidx < tc->peer_cnt; pidx++) {
		tc->peers[pidx].inmw_cnt = ntb_mw_count(tc->dev);
		tc->peers[pidx].inmws = malloc(tc->peers[pidx].inmw_cnt *
		    sizeof(*tc->peers[pidx].inmws), M_NTB_TOOL,
		    M_WAITOK | M_ZERO);
		if (tc->peers[pidx].inmws == NULL)
			return (ENOMEM);

		for (widx = 0; widx < tc->peers[pidx].inmw_cnt; widx++) {
			mw = &tc->peers[pidx].inmws[widx];
			memset((void *)mw, 0, sizeof(*mw));
			mw->tc = tc;
			mw->widx = widx;
			mw->pidx = pidx;
			mw->mw_buf_offset = DEFAULT_MW_OFF;
			mw->mw_buf_size = DEFAULT_MW_SIZE;
			/* get the tx buff details for each mw attached with each peer */
			rc = ntb_mw_get_range(tc->dev, widx, &mw->phys_addr,
			    &mw->mm_base, &mw->phys_size, &mw->xlat_align,
			    &mw->xlat_align_size, &mw->addr_limit);
			if (rc)
				goto free_mws;
		}
	}

	return (0);

free_mws:
	tool_clear_mws(tc);
	return (rc);
}