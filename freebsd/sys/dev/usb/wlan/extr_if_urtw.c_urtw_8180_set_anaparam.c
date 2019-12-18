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
typedef  scalar_t__ usb_error_t ;
typedef  int uint8_t ;
typedef  int /*<<< orphan*/  uint32_t ;
struct urtw_softc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  URTW_ANAPARAM ; 
 int /*<<< orphan*/  URTW_CONFIG3 ; 
 int URTW_CONFIG3_ANAPARAM_WRITE ; 
 int /*<<< orphan*/  URTW_EPROM_CMD_CONFIG ; 
 int /*<<< orphan*/  URTW_EPROM_CMD_NORMAL ; 
 int /*<<< orphan*/  urtw_read8_m (struct urtw_softc*,int /*<<< orphan*/ ,int*) ; 
 scalar_t__ urtw_set_mode (struct urtw_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  urtw_write32_m (struct urtw_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  urtw_write8_m (struct urtw_softc*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static usb_error_t
urtw_8180_set_anaparam(struct urtw_softc *sc, uint32_t val)
{
	uint8_t data;
	usb_error_t error;

	error = urtw_set_mode(sc, URTW_EPROM_CMD_CONFIG);
	if (error)
		goto fail;

	urtw_read8_m(sc, URTW_CONFIG3, &data);
	urtw_write8_m(sc, URTW_CONFIG3, data | URTW_CONFIG3_ANAPARAM_WRITE);
	urtw_write32_m(sc, URTW_ANAPARAM, val);
	urtw_read8_m(sc, URTW_CONFIG3, &data);
	urtw_write8_m(sc, URTW_CONFIG3, data & ~URTW_CONFIG3_ANAPARAM_WRITE);

	error = urtw_set_mode(sc, URTW_EPROM_CMD_NORMAL);
	if (error)
		goto fail;
fail:
	return (error);
}