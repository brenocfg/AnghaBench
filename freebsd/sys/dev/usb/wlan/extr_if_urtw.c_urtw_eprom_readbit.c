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
typedef  int /*<<< orphan*/  usb_error_t ;
typedef  int uint8_t ;
struct urtw_softc {int dummy; } ;
typedef  int int16_t ;

/* Variables and functions */
 int /*<<< orphan*/  DELAY (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  URTW_EPROM_CMD ; 
 int /*<<< orphan*/  URTW_EPROM_DELAY ; 
 int URTW_EPROM_READBIT ; 
 int /*<<< orphan*/  urtw_read8_m (struct urtw_softc*,int /*<<< orphan*/ ,int*) ; 

__attribute__((used)) static usb_error_t
urtw_eprom_readbit(struct urtw_softc *sc, int16_t *data)
{
	uint8_t data8;
	usb_error_t error;

	urtw_read8_m(sc, URTW_EPROM_CMD, &data8);
	*data = (data8 & URTW_EPROM_READBIT) ? 1 : 0;
	DELAY(URTW_EPROM_DELAY);

fail:
	return (error);
}