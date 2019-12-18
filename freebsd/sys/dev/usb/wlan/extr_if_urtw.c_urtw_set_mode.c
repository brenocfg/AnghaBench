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
typedef  int uint32_t ;
struct urtw_softc {int dummy; } ;

/* Variables and functions */
 int URTW_EPROM_CK ; 
 int /*<<< orphan*/  URTW_EPROM_CMD ; 
 int URTW_EPROM_CMD_MASK ; 
 int URTW_EPROM_CMD_SHIFT ; 
 int URTW_EPROM_CS ; 
 int /*<<< orphan*/  urtw_read8_m (struct urtw_softc*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  urtw_write8_m (struct urtw_softc*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static usb_error_t
urtw_set_mode(struct urtw_softc *sc, uint32_t mode)
{
	uint8_t data;
	usb_error_t error;

	urtw_read8_m(sc, URTW_EPROM_CMD, &data);
	data = (data & ~URTW_EPROM_CMD_MASK) | (mode << URTW_EPROM_CMD_SHIFT);
	data = data & ~(URTW_EPROM_CS | URTW_EPROM_CK);
	urtw_write8_m(sc, URTW_EPROM_CMD, data);
fail:
	return (error);
}