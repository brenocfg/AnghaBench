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
 int /*<<< orphan*/  R92C_CAMCMD ; 
 int R92C_CAMCMD_CLR ; 
 int R92C_CAMCMD_POLLING ; 
 int /*<<< orphan*/  rtwn_write_4 (struct rtwn_softc*,int /*<<< orphan*/ ,int) ; 

void
rtwn_init_cam(struct rtwn_softc *sc)
{
	/* Invalidate all CAM entries. */
	rtwn_write_4(sc, R92C_CAMCMD,
	    R92C_CAMCMD_POLLING | R92C_CAMCMD_CLR);
}