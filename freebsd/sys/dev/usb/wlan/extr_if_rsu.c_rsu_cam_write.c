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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int uint32_t ;
struct rsu_softc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  R92S_CAMCMD ; 
 int /*<<< orphan*/  R92S_CAMCMD_ADDR ; 
 int R92S_CAMCMD_POLLING ; 
 int R92S_CAMCMD_WRITE ; 
 int /*<<< orphan*/  R92S_CAMWRITE ; 
 int SM (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rsu_write_4 (struct rsu_softc*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
rsu_cam_write(struct rsu_softc *sc, uint8_t addr, uint32_t data)
{

	rsu_write_4(sc, R92S_CAMWRITE, data);
	rsu_write_4(sc, R92S_CAMCMD,
	    R92S_CAMCMD_POLLING | R92S_CAMCMD_WRITE |
	    SM(R92S_CAMCMD_ADDR, addr));
}