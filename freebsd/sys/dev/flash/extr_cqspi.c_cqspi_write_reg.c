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
typedef  int /*<<< orphan*/  uint32_t ;
struct cqspi_softc {int dummy; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int cqspi_cmd_write (struct cqspi_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct cqspi_softc* device_get_softc (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
cqspi_write_reg(device_t dev, device_t child,
    uint8_t opcode, uint8_t *addr, uint32_t len)
{
	struct cqspi_softc *sc;
	int ret;

	sc = device_get_softc(dev);

	ret = cqspi_cmd_write(sc, opcode, addr, len);

	return (ret);
}