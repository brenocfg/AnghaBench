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
typedef  int /*<<< orphan*/  u_int ;
struct pcib_softc {int dummy; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int PCIB_READ_CONFIG (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  device_get_parent (int /*<<< orphan*/ ) ; 
 struct pcib_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pcib_present (struct pcib_softc*) ; 
 int /*<<< orphan*/  pcib_xlate_ari (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static uint32_t
pcib_read_config(device_t dev, u_int b, u_int s, u_int f, u_int reg, int width)
{
#ifdef PCI_HP
	struct pcib_softc *sc;

	sc = device_get_softc(dev);
	if (!pcib_present(sc)) {
		switch (width) {
		case 2:
			return (0xffff);
		case 1:
			return (0xff);
		default:
			return (0xffffffff);
		}
	}
#endif
	pcib_xlate_ari(dev, b, &s, &f);
	return(PCIB_READ_CONFIG(device_get_parent(device_get_parent(dev)), b, s,
	    f, reg, width));
}