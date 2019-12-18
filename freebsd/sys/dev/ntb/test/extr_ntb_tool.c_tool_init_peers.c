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
struct tool_ctx {int peer_cnt; TYPE_1__* peers; int /*<<< orphan*/  dev; } ;
struct TYPE_2__ {int pidx; struct tool_ctx* tc; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  M_NTB_TOOL ; 
 int M_WAITOK ; 
 int M_ZERO ; 
 TYPE_1__* malloc (int,int /*<<< orphan*/ ,int) ; 
 int ntb_peer_port_count (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
tool_init_peers(struct tool_ctx *tc)
{
	int pidx;

	tc->peer_cnt = ntb_peer_port_count(tc->dev);
	tc->peers = malloc(tc->peer_cnt * sizeof(*tc->peers), M_NTB_TOOL,
	    M_WAITOK | M_ZERO);
	if (tc->peers == NULL)
		return (ENOMEM);
	for (pidx = 0; pidx < tc->peer_cnt; pidx++) {
		tc->peers[pidx].pidx = pidx;
		tc->peers[pidx].tc = tc;
	}

	return (0);
}