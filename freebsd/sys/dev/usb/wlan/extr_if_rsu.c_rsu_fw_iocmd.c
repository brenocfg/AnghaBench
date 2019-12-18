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
typedef  int /*<<< orphan*/  uint32_t ;
struct rsu_softc {int dummy; } ;

/* Variables and functions */
 int ETIMEDOUT ; 
 int /*<<< orphan*/  R92S_IOCMD_CTRL ; 
 int /*<<< orphan*/  rsu_ms_delay (struct rsu_softc*,int) ; 
 scalar_t__ rsu_read_4 (struct rsu_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rsu_write_4 (struct rsu_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
rsu_fw_iocmd(struct rsu_softc *sc, uint32_t iocmd)
{
	int ntries;

	rsu_write_4(sc, R92S_IOCMD_CTRL, iocmd);
	rsu_ms_delay(sc, 1);
	for (ntries = 0; ntries < 50; ntries++) {
		if (rsu_read_4(sc, R92S_IOCMD_CTRL) == 0)
			return (0);
		rsu_ms_delay(sc, 1);
	}
	return (ETIMEDOUT);
}