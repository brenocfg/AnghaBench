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
struct openpic_softc {int dummy; } ;
typedef  enum intr_trigger { ____Placeholder_intr_trigger } intr_trigger ;
typedef  enum intr_polarity { ____Placeholder_intr_polarity } intr_polarity ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int INTR_POLARITY_LOW ; 
 int INTR_TRIGGER_EDGE ; 
 int /*<<< orphan*/  OPENPIC_POLARITY_POSITIVE ; 
 int /*<<< orphan*/  OPENPIC_SENSE_LEVEL ; 
 int /*<<< orphan*/  OPENPIC_SRC_VECTOR (int /*<<< orphan*/ ) ; 
 struct openpic_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  openpic_read (struct openpic_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  openpic_write (struct openpic_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
openpic_config(device_t dev, u_int irq, enum intr_trigger trig,
    enum intr_polarity pol)
{
	struct openpic_softc *sc;
	uint32_t x;

	sc = device_get_softc(dev);
	x = openpic_read(sc, OPENPIC_SRC_VECTOR(irq));
	if (pol == INTR_POLARITY_LOW)
		x &= ~OPENPIC_POLARITY_POSITIVE;
	else
		x |= OPENPIC_POLARITY_POSITIVE;
	if (trig == INTR_TRIGGER_EDGE)
		x &= ~OPENPIC_SENSE_LEVEL;
	else
		x |= OPENPIC_SENSE_LEVEL;
	openpic_write(sc, OPENPIC_SRC_VECTOR(irq), x);
}