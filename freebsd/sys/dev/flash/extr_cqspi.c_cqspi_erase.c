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
struct cqspi_softc {int dummy; } ;
typedef  int /*<<< orphan*/  off_t ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  CMD_QUAD_SECTOR_ERASE ; 
 int /*<<< orphan*/  CMD_WRITE_ENABLE ; 
 int cqspi_cmd_write (struct cqspi_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int cqspi_cmd_write_addr (struct cqspi_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  cqspi_wait_idle (struct cqspi_softc*) ; 
 int /*<<< orphan*/  cqspi_wait_ready (struct cqspi_softc*) ; 
 struct cqspi_softc* device_get_softc (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
cqspi_erase(device_t dev, device_t child, off_t offset)
{
	struct cqspi_softc *sc;
	int ret;

	sc = device_get_softc(dev);

	cqspi_wait_idle(sc);
	cqspi_wait_ready(sc);
	ret = cqspi_cmd_write(sc, CMD_WRITE_ENABLE, 0, 0);

	cqspi_wait_idle(sc);
	cqspi_wait_ready(sc);
	ret = cqspi_cmd_write_addr(sc, CMD_QUAD_SECTOR_ERASE, offset, 4);

	cqspi_wait_idle(sc);

	return (0);
}