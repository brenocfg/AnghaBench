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
struct edma_softc {int dummy; } ;
struct edma_channel {int /*<<< orphan*/  mux_chn; int /*<<< orphan*/  mux_src; int /*<<< orphan*/  mux_num; scalar_t__ enabled; } ;

/* Variables and functions */
 int /*<<< orphan*/  dmamux_configure (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct edma_channel* edma_map ; 

__attribute__((used)) static int
channel_free(struct edma_softc *sc, int chnum)
{
	struct edma_channel *ch;

	ch = &edma_map[chnum];
	ch->enabled = 0;

	dmamux_configure(ch->mux_num, ch->mux_src, ch->mux_chn, 0);

	return (0);
}