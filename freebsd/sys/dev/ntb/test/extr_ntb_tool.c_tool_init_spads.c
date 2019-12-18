#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct tool_ctx {int inspad_cnt; int peer_cnt; TYPE_3__* peers; int /*<<< orphan*/  dev; TYPE_1__* inspads; } ;
struct TYPE_6__ {int outspad_cnt; TYPE_2__* outspads; } ;
struct TYPE_5__ {int sidx; int pidx; struct tool_ctx* tc; } ;
struct TYPE_4__ {int sidx; int pidx; struct tool_ctx* tc; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  M_NTB_TOOL ; 
 int M_WAITOK ; 
 int M_ZERO ; 
 void* malloc (int,int /*<<< orphan*/ ,int) ; 
 void* ntb_spad_count (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
tool_init_spads(struct tool_ctx *tc)
{
	int sidx, pidx;

	/* Initialize inbound scratchpad structures */
	tc->inspad_cnt = ntb_spad_count(tc->dev);
	tc->inspads = malloc(tc->inspad_cnt * sizeof(*tc->inspads), M_NTB_TOOL,
	    M_WAITOK | M_ZERO);
	if (tc->inspads == NULL)
		return (ENOMEM);

	for (sidx = 0; sidx < tc->inspad_cnt; sidx++) {
		tc->inspads[sidx].sidx = sidx;
		tc->inspads[sidx].pidx = -1;
		tc->inspads[sidx].tc = tc;
	}

	/* Initialize outbound scratchpad structures */
	for (pidx = 0; pidx < tc->peer_cnt; pidx++) {
		tc->peers[pidx].outspad_cnt = ntb_spad_count(tc->dev);
		tc->peers[pidx].outspads =  malloc(tc->peers[pidx].outspad_cnt *
		    sizeof(*tc->peers[pidx].outspads), M_NTB_TOOL, M_WAITOK |
		    M_ZERO);
		if (tc->peers[pidx].outspads == NULL)
			return (ENOMEM);

		for (sidx = 0; sidx < tc->peers[pidx].outspad_cnt; sidx++) {
			tc->peers[pidx].outspads[sidx].sidx = sidx;
			tc->peers[pidx].outspads[sidx].pidx = pidx;
			tc->peers[pidx].outspads[sidx].tc = tc;
		}
	}

	return (0);
}