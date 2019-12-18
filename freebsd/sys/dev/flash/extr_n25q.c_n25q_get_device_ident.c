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
typedef  int uint8_t ;
typedef  int uint16_t ;
struct n25q_softc {int /*<<< orphan*/  dev; } ;
struct n25q_flash_ident {int manufacturer_id; int device_id; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  CMD_READ_IDENT ; 
 int /*<<< orphan*/  QSPI_READ_REG (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int) ; 
 int /*<<< orphan*/  device_get_parent (int /*<<< orphan*/ ) ; 
 struct n25q_flash_ident* flash_devices ; 
 int nitems (struct n25q_flash_ident*) ; 
 int /*<<< orphan*/  printf (char*,int,int) ; 

__attribute__((used)) static struct n25q_flash_ident*
n25q_get_device_ident(struct n25q_softc *sc)
{
	uint8_t manufacturer_id;
	uint16_t dev_id;
	device_t pdev;
	uint8_t data[4];
	int i;

	pdev = device_get_parent(sc->dev);

	QSPI_READ_REG(pdev, sc->dev, CMD_READ_IDENT, (uint8_t *)&data[0], 4);

	manufacturer_id = data[0];
	dev_id = (data[1] << 8) | (data[2]);

	for (i = 0; i < nitems(flash_devices); i++) {
		if ((flash_devices[i].manufacturer_id == manufacturer_id) &&
		    (flash_devices[i].device_id == dev_id))
			return &flash_devices[i];
	}

	printf("Unknown SPI flash device. Vendor: %02x, device id: %04x\n",
	    manufacturer_id, dev_id);

	return (NULL);
}