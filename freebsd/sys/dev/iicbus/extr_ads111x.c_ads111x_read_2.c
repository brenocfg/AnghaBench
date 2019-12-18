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
struct ads111x_softc {int /*<<< orphan*/  dev; } ;
typedef  int int16_t ;

/* Variables and functions */
 int /*<<< orphan*/  IIC_WAIT ; 
 scalar_t__ be16dec (int /*<<< orphan*/ *) ; 
 int iic2errno (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iicdev_readfrom (int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
ads111x_read_2(struct ads111x_softc *sc, int reg, int *val) 
{
	int err;
	uint8_t data[2];

	err = iic2errno(iicdev_readfrom(sc->dev, reg, data, 2, IIC_WAIT));
	if (err == 0)
		*val = (int16_t)be16dec(data);

	return (err);
}