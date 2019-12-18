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
typedef  int uint64_t ;
struct sec_softc {int dummy; } ;

/* Variables and functions */
 int SEC_CHANNELS ; 
 int /*<<< orphan*/  SEC_IER ; 
 int SEC_INT_CH_DN (int) ; 
 int SEC_INT_CH_ERR (int) ; 
 int SEC_INT_ITO ; 
 int /*<<< orphan*/  SEC_WRITE (struct sec_softc*,int /*<<< orphan*/ ,int) ; 
 int sec_channel_reset (struct sec_softc*,int,int) ; 
 int sec_controller_reset (struct sec_softc*) ; 

__attribute__((used)) static int
sec_init(struct sec_softc *sc)
{
	uint64_t reg;
	int error, i;

	/* Reset controller twice to clear all pending interrupts */
	error = sec_controller_reset(sc);
	if (error)
		return (error);

	error = sec_controller_reset(sc);
	if (error)
		return (error);

	/* Reset channels */
	for (i = 0; i < SEC_CHANNELS; i++) {
		error = sec_channel_reset(sc, i, 1);
		if (error)
			return (error);
	}

	/* Enable Interrupts */
	reg = SEC_INT_ITO;
	for (i = 0; i < SEC_CHANNELS; i++)
		reg |= SEC_INT_CH_DN(i) | SEC_INT_CH_ERR(i);

	SEC_WRITE(sc, SEC_IER, reg);

	return (error);
}