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
typedef  int /*<<< orphan*/  u_int ;
struct pcib_softc {int dummy; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  PCIB_WRITE_CONFIG (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  device_get_parent (int /*<<< orphan*/ ) ; 
 struct pcib_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pcib_present (struct pcib_softc*) ; 
 int /*<<< orphan*/  pcib_xlate_ari (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
pcib_write_config(device_t dev, u_int b, u_int s, u_int f, u_int reg, uint32_t val, int width)
{
#ifdef PCI_HP
	struct pcib_softc *sc;

	sc = device_get_softc(dev);
	if (!pcib_present(sc))
		return;
#endif
	pcib_xlate_ari(dev, b, &s, &f);
	PCIB_WRITE_CONFIG(device_get_parent(device_get_parent(dev)), b, s, f,
	    reg, val, width);
}