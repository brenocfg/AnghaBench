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
struct pmufreq_softc {int /*<<< orphan*/  curfreq; } ;
struct cf_setting {int /*<<< orphan*/  dev; int /*<<< orphan*/  freq; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int EINVAL ; 
 struct pmufreq_softc* device_get_softc (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
pmufreq_get(device_t dev, struct cf_setting *set)
{
	struct pmufreq_softc *sc;

	if (set == NULL)
		return (EINVAL);
	sc = device_get_softc(dev);

	set->freq = sc->curfreq;
	set->dev = dev;

	return (0);
}