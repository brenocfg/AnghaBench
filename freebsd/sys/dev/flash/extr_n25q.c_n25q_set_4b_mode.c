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
struct n25q_softc {int dummy; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int QSPI_WRITE_REG (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_get_parent (int /*<<< orphan*/ ) ; 
 struct n25q_softc* device_get_softc (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
n25q_set_4b_mode(device_t dev, uint8_t command)
{
	struct n25q_softc *sc;
	device_t pdev;
	int err;

	pdev = device_get_parent(dev);
	sc = device_get_softc(dev);

	err = QSPI_WRITE_REG(pdev, dev, command, 0, 0);

	return (err);
}