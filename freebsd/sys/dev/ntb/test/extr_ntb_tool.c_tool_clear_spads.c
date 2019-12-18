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
struct tool_ctx {int peer_cnt; TYPE_1__* peers; int /*<<< orphan*/  inspads; } ;
struct TYPE_2__ {int /*<<< orphan*/  outspads; } ;

/* Variables and functions */
 int /*<<< orphan*/  M_NTB_TOOL ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
tool_clear_spads(struct tool_ctx *tc)
{
	int pidx;

	/* Free local inspads. */
	free(tc->inspads, M_NTB_TOOL);

	/* Free outspads for each peer. */
	for (pidx = 0; pidx < tc->peer_cnt; pidx++)
		free(tc->peers[pidx].outspads, M_NTB_TOOL);
}