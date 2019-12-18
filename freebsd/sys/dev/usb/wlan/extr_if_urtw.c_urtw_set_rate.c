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
typedef  int uint16_t ;
struct urtw_softc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  URTW_BRSR ; 
 int URTW_BRSR_MBR_8185 ; 
 int URTW_RESP_MAX_RATE_SHIFT ; 
 int URTW_RESP_MIN_RATE_SHIFT ; 
 int /*<<< orphan*/  URTW_RESP_RATE ; 
 int URTW_RIDX_OFDM24 ; 
 int URTW_RIDX_OFDM6 ; 
 int /*<<< orphan*/  urtw_read16_m (struct urtw_softc*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  urtw_write16_m (struct urtw_softc*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  urtw_write8_m (struct urtw_softc*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static usb_error_t
urtw_set_rate(struct urtw_softc *sc)
{
	int i, basic_rate, min_rr_rate, max_rr_rate;
	uint16_t data;
	usb_error_t error;

	basic_rate = URTW_RIDX_OFDM24;
	min_rr_rate = URTW_RIDX_OFDM6;
	max_rr_rate = URTW_RIDX_OFDM24;

	urtw_write8_m(sc, URTW_RESP_RATE,
	    max_rr_rate << URTW_RESP_MAX_RATE_SHIFT |
	    min_rr_rate << URTW_RESP_MIN_RATE_SHIFT);

	urtw_read16_m(sc, URTW_BRSR, &data);
	data &= ~URTW_BRSR_MBR_8185;

	for (i = 0; i <= basic_rate; i++)
		data |= (1 << i);

	urtw_write16_m(sc, URTW_BRSR, data);
fail:
	return (error);
}