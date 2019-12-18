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
typedef  int uint32_t ;
struct rtwn_softc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  R92C_CAMCMD ; 
 int /*<<< orphan*/  R92C_CAMCMD_ADDR ; 
 int R92C_CAMCMD_POLLING ; 
 int R92C_CAMCMD_WRITE ; 
 int /*<<< orphan*/  R92C_CAMWRITE ; 
 int SM (int /*<<< orphan*/ ,int) ; 
 int rtwn_write_4 (struct rtwn_softc*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int
rtwn_cam_write(struct rtwn_softc *sc, uint32_t addr, uint32_t data)
{
	int error;

	error = rtwn_write_4(sc, R92C_CAMWRITE, data);
	if (error != 0)
		return (error);
	error = rtwn_write_4(sc, R92C_CAMCMD,
	    R92C_CAMCMD_POLLING | R92C_CAMCMD_WRITE |
	    SM(R92C_CAMCMD_ADDR, addr));

	return (error);
}