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
struct rtwn_softc {int dummy; } ;

/* Variables and functions */
 int rtwn_bb_read (struct rtwn_softc*,int) ; 

__attribute__((used)) static int
r21au_dfs_radar_is_enabled(struct rtwn_softc *sc)
{
	return !!(rtwn_bb_read(sc, 0x924) & 0x00008000);
}