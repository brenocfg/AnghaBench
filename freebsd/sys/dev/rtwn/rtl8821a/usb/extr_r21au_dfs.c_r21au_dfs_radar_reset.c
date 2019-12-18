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
 int rtwn_bb_setbits (struct rtwn_softc*,int,int,int) ; 

__attribute__((used)) static int
r21au_dfs_radar_reset(struct rtwn_softc *sc)
{
	int error;

	error = rtwn_bb_setbits(sc, 0x924, 0x00008000, 0);
	if (error != 0)
		return (error);

	return (rtwn_bb_setbits(sc, 0x924, 0, 0x00008000));
}