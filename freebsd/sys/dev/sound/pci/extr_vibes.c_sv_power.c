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
typedef  int u_int8_t ;
struct sc_info {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEB (int /*<<< orphan*/ ) ; 
 int SV_ANALOG_OFF ; 
 int SV_ANALOG_OFF_SPLL ; 
 int SV_ANALOG_OFF_SRS ; 
 int SV_DIGITAL_OFF ; 
 int SV_DIGITAL_OFF_GP ; 
 int SV_DIGITAL_OFF_MU ; 
 int SV_DIGITAL_OFF_SYN ; 
 int /*<<< orphan*/  SV_REG_ANALOG_PWR ; 
 int /*<<< orphan*/  SV_REG_DIGITAL_PWR ; 
 int /*<<< orphan*/  printf (char*,int) ; 
 int sv_indirect_get (struct sc_info*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sv_indirect_set (struct sc_info*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
sv_power(struct sc_info *sc, int state)
{
	u_int8_t v;

        switch (state) {
        case 0:
		/* power on */
		v = sv_indirect_get(sc, SV_REG_ANALOG_PWR) &~ SV_ANALOG_OFF;
		v |= SV_ANALOG_OFF_SRS | SV_ANALOG_OFF_SPLL;
		sv_indirect_set(sc, SV_REG_ANALOG_PWR, v);
		v = sv_indirect_get(sc, SV_REG_DIGITAL_PWR) &~ SV_DIGITAL_OFF;
		v |= SV_DIGITAL_OFF_SYN | SV_DIGITAL_OFF_MU | SV_DIGITAL_OFF_GP;
		sv_indirect_set(sc, SV_REG_DIGITAL_PWR, v);
                break;
        default:
		/* power off */
		v = sv_indirect_get(sc, SV_REG_ANALOG_PWR) | SV_ANALOG_OFF;
		sv_indirect_set(sc, SV_REG_ANALOG_PWR, v);
		v = sv_indirect_get(sc, SV_REG_DIGITAL_PWR) | SV_DIGITAL_OFF;
		sv_indirect_set(sc, SV_REG_DIGITAL_PWR, SV_DIGITAL_OFF);
                break;
        }
        DEB(printf("Power state %d\n", state));
}