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
struct amdtemp_softc {int /*<<< orphan*/  sc_offset; } ;
typedef  int /*<<< orphan*/  int32_t ;
typedef  int /*<<< orphan*/  device_t ;
typedef  int /*<<< orphan*/  amdsensor_t ;

/* Variables and functions */
 int /*<<< orphan*/  AMDTEMP_REPTMP_CTRL ; 
 int /*<<< orphan*/  amdtemp_decode_fam10h_to_16h (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct amdtemp_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_read_config (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int32_t
amdtemp_gettemp(device_t dev, amdsensor_t sensor)
{
	struct amdtemp_softc *sc = device_get_softc(dev);
	uint32_t temp;

	temp = pci_read_config(dev, AMDTEMP_REPTMP_CTRL, 4);
	return (amdtemp_decode_fam10h_to_16h(sc->sc_offset, temp));
}