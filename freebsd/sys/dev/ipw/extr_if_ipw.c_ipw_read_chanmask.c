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
typedef  int uint16_t ;
struct ipw_softc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  IPW_EEPROM_CHANNEL_LIST ; 
 int ipw_read_prom_word (struct ipw_softc*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static uint16_t
ipw_read_chanmask(struct ipw_softc *sc)
{
	uint16_t val;

	/* set supported .11b channels (read from EEPROM) */
	if ((val = ipw_read_prom_word(sc, IPW_EEPROM_CHANNEL_LIST)) == 0)
		val = 0x7ff;	/* default to channels 1-11 */
	val <<= 1;

	return (val);
}