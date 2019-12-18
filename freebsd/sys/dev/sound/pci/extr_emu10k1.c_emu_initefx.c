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
typedef  int u_int32_t ;
struct sc_info {scalar_t__ APS; } ;

/* Variables and functions */
 int /*<<< orphan*/  C_00000000 ; 
 int /*<<< orphan*/  C_00000001 ; 
 int /*<<< orphan*/  C_00000004 ; 
 int /*<<< orphan*/  C_40000000 ; 
 scalar_t__ EMU_DBG ; 
 scalar_t__ EMU_FXGPREGBASE ; 
 int /*<<< orphan*/  EXTIN (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EXTIN_AC97_L ; 
 int /*<<< orphan*/  EXTIN_AC97_R ; 
 int /*<<< orphan*/  EXTIN_SPDIF_CD_L ; 
 int /*<<< orphan*/  EXTIN_SPDIF_CD_R ; 
 int /*<<< orphan*/  EXTIN_TOSLINK_L ; 
 int /*<<< orphan*/  EXTIN_TOSLINK_R ; 
 int /*<<< orphan*/  EXTOUT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EXTOUT_AC97_CENTER ; 
 int /*<<< orphan*/  EXTOUT_AC97_L ; 
 int /*<<< orphan*/  EXTOUT_AC97_LFE ; 
 int /*<<< orphan*/  EXTOUT_AC97_R ; 
 int /*<<< orphan*/  EXTOUT_ACENTER ; 
 int /*<<< orphan*/  EXTOUT_ADC_CAP_L ; 
 int /*<<< orphan*/  EXTOUT_ADC_CAP_R ; 
 int /*<<< orphan*/  EXTOUT_ALFE ; 
 int /*<<< orphan*/  EXTOUT_HEADPHONE_L ; 
 int /*<<< orphan*/  EXTOUT_HEADPHONE_R ; 
 int /*<<< orphan*/  EXTOUT_REAR_L ; 
 int /*<<< orphan*/  EXTOUT_REAR_R ; 
 int /*<<< orphan*/  EXTOUT_TOSLINK_L ; 
 int /*<<< orphan*/  EXTOUT_TOSLINK_R ; 
 int /*<<< orphan*/  FXBUS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FXBUS_PCM_LEFT ; 
 int /*<<< orphan*/  FXBUS_PCM_RIGHT ; 
 int /*<<< orphan*/  GPR (int) ; 
 int /*<<< orphan*/  emu_addefxop (struct sc_info*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  emu_wrefx (struct sc_info*,int,int) ; 
 int /*<<< orphan*/  emu_wrptr (struct sc_info*,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iACC3 ; 
 int /*<<< orphan*/  iINTERP ; 
 int /*<<< orphan*/  iMAC0 ; 
 int /*<<< orphan*/  iMACINT0 ; 

__attribute__((used)) static void
emu_initefx(struct sc_info *sc)
{
	int i;
	u_int32_t pc = 16;

	/* acc3 0,0,0,0 - NOPs */
	for (i = 0; i < 512; i++) {
		emu_wrefx(sc, i * 2, 0x10040);
		emu_wrefx(sc, i * 2 + 1, 0x610040);
	}

	for (i = 0; i < 256; i++)
		emu_wrptr(sc, 0, EMU_FXGPREGBASE + i, 0);

	/* FX-8010 DSP Registers:
	   FX Bus
	     0x000-0x00f : 16 registers
	   Input
	     0x010/0x011 : AC97 Codec (l/r)
	     0x012/0x013 : ADC, S/PDIF (l/r)
	     0x014/0x015 : Mic(left), Zoom (l/r)
	     0x016/0x017 : TOS link in (l/r)
	     0x018/0x019 : Line/Mic 1 (l/r)
	     0x01a/0x01b : COAX S/PDIF (l/r)
	     0x01c/0x01d : Line/Mic 2 (l/r)
	   Output
	     0x020/0x021 : AC97 Output (l/r)
	     0x022/0x023 : TOS link out (l/r)
	     0x024/0x025 : Center/LFE
	     0x026/0x027 : LiveDrive Headphone (l/r)
	     0x028/0x029 : Rear Channel (l/r)
	     0x02a/0x02b : ADC Recording Buffer (l/r)
	     0x02c       : Mic Recording Buffer
	     0x031/0x032 : Analog Center/LFE
	   Constants
	     0x040 - 0x044 = 0 - 4
	     0x045 = 0x8, 0x046 = 0x10, 0x047 = 0x20
	     0x048 = 0x100, 0x049 = 0x10000, 0x04a = 0x80000
	     0x04b = 0x10000000, 0x04c = 0x20000000, 0x04d = 0x40000000
	     0x04e = 0x80000000, 0x04f = 0x7fffffff, 0x050 = 0xffffffff
	     0x051 = 0xfffffffe, 0x052 = 0xc0000000, 0x053 = 0x41fbbcdc
	     0x054 = 0x5a7ef9db, 0x055 = 0x00100000
	   Temporary Values
	     0x056 : Accumulator
	     0x057 : Condition Register
	     0x058 : Noise source
	     0x059 : Noise source
	     0x05a : IRQ Register
	     0x05b : TRAM Delay Base Address Count
	   General Purpose Registers
	     0x100 - 0x1ff
	   Tank Memory Data Registers
	     0x200 - 0x2ff
	   Tank Memory Address Registers
	     0x300 - 0x3ff
	     */

	/* Routing - this will be configurable in later version */

	/* GPR[0/1] = FX * 4 + SPDIF-in */
	emu_addefxop(sc, iMACINT0, GPR(0), EXTIN(EXTIN_SPDIF_CD_L),
			FXBUS(FXBUS_PCM_LEFT), C_00000004, &pc);
	emu_addefxop(sc, iMACINT0, GPR(1), EXTIN(EXTIN_SPDIF_CD_R),
			FXBUS(FXBUS_PCM_RIGHT), C_00000004, &pc);

	/* GPR[0/1] += APS-input */
	emu_addefxop(sc, iACC3, GPR(0), GPR(0), C_00000000,
			sc->APS ? EXTIN(EXTIN_TOSLINK_L) : C_00000000, &pc);
	emu_addefxop(sc, iACC3, GPR(1), GPR(1), C_00000000,
			sc->APS ? EXTIN(EXTIN_TOSLINK_R) : C_00000000, &pc);

	/* FrontOut (AC97) = GPR[0/1] */
	emu_addefxop(sc, iACC3, EXTOUT(EXTOUT_AC97_L), C_00000000,
			C_00000000, GPR(0), &pc);
	emu_addefxop(sc, iACC3, EXTOUT(EXTOUT_AC97_R), C_00000000,
			C_00000001, GPR(1), &pc);

	/* GPR[2] = GPR[0] (Left) / 2 + GPR[1] (Right) / 2 -- Central volume */
	emu_addefxop(sc, iINTERP, GPR(2), GPR(1), C_40000000, GPR(0), &pc);

#if 0
	/* RearOut = (GPR[0/1] * RearVolume) >> 31 */
	/*   RearVolume = GPR[0x10/0x11] */
	emu_addefxop(sc, iMAC0, EXTOUT(EXTOUT_REAR_L), C_00000000,
			GPR(16), GPR(0), &pc);
	emu_addefxop(sc, iMAC0, EXTOUT(EXTOUT_REAR_R), C_00000000,
			GPR(17), GPR(1), &pc);
#else
	/* XXX This is just a copy to the channel, since we do not have
	 *     a patch manager, it is useful for have another output enabled.
	 */

	/* Rear[l/r] = GPR[0/1] */
	emu_addefxop(sc, iACC3, EXTOUT(EXTOUT_REAR_L), C_00000000,
			C_00000000, GPR(0), &pc);
	emu_addefxop(sc, iACC3, EXTOUT(EXTOUT_REAR_R), C_00000000,
			C_00000000, GPR(1), &pc);
#endif

	/* TOS out[l/r] = GPR[0/1] */
	emu_addefxop(sc, iACC3, EXTOUT(EXTOUT_TOSLINK_L), C_00000000,
			C_00000000, GPR(0), &pc);
	emu_addefxop(sc, iACC3, EXTOUT(EXTOUT_TOSLINK_R), C_00000000,
			C_00000000, GPR(1), &pc);

	/* Center and Subwoofer configuration */
	/* Analog Center = GPR[0] + GPR[2] */
	emu_addefxop(sc, iACC3, EXTOUT(EXTOUT_ACENTER), C_00000000,
			GPR(0), GPR(2), &pc);
	/* Analog Sub = GPR[1] + GPR[2] */
	emu_addefxop(sc, iACC3, EXTOUT(EXTOUT_ALFE), C_00000000,
			GPR(1), GPR(2), &pc);
	/* Digital Center = GPR[0] + GPR[2] */
	emu_addefxop(sc, iACC3, EXTOUT(EXTOUT_AC97_CENTER), C_00000000,
			GPR(0), GPR(2), &pc);
	/* Digital Sub = GPR[1] + GPR[2] */
	emu_addefxop(sc, iACC3, EXTOUT(EXTOUT_AC97_LFE), C_00000000,
			GPR(1), GPR(2), &pc);

	/* Headphones[l/r] = GPR[0/1] */
	emu_addefxop(sc, iACC3, EXTOUT(EXTOUT_HEADPHONE_L), C_00000000,
			C_00000000, GPR(0), &pc);
	emu_addefxop(sc, iACC3, EXTOUT(EXTOUT_HEADPHONE_R), C_00000000,
			C_00000000, GPR(1), &pc);

	/* ADC Recording buffer[l/r] = AC97Input[l/r] */
	emu_addefxop(sc, iACC3, EXTOUT(EXTOUT_ADC_CAP_L), C_00000000,
			C_00000000, EXTIN(EXTIN_AC97_L), &pc);
	emu_addefxop(sc, iACC3, EXTOUT(EXTOUT_ADC_CAP_R), C_00000000,
			C_00000000, EXTIN(EXTIN_AC97_R), &pc);

	/* resume normal operations */
	emu_wrptr(sc, 0, EMU_DBG, 0);
}