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
struct sc_info {int dummy; } ;

/* Variables and functions */
 int A_C_00000000 ; 
 int A_C_40000000 ; 
 int A_EXTIN (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  A_EXTIN_AC97_L ; 
 int /*<<< orphan*/  A_EXTIN_AC97_R ; 
 int A_EXTOUT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  A_EXTOUT_AC97_L ; 
 int /*<<< orphan*/  A_EXTOUT_AC97_R ; 
 int /*<<< orphan*/  A_EXTOUT_ACENTER ; 
 int /*<<< orphan*/  A_EXTOUT_ADC_CAP_L ; 
 int /*<<< orphan*/  A_EXTOUT_ADC_CAP_R ; 
 int /*<<< orphan*/  A_EXTOUT_AFRONT_L ; 
 int /*<<< orphan*/  A_EXTOUT_AFRONT_R ; 
 int /*<<< orphan*/  A_EXTOUT_ALFE ; 
 int /*<<< orphan*/  A_EXTOUT_AREAR_L ; 
 int /*<<< orphan*/  A_EXTOUT_AREAR_R ; 
 int /*<<< orphan*/  A_EXTOUT_CENTER ; 
 int /*<<< orphan*/  A_EXTOUT_FRONT_L ; 
 int /*<<< orphan*/  A_EXTOUT_FRONT_R ; 
 int /*<<< orphan*/  A_EXTOUT_HEADPHONE_L ; 
 int /*<<< orphan*/  A_EXTOUT_HEADPHONE_R ; 
 int /*<<< orphan*/  A_EXTOUT_LFE ; 
 int /*<<< orphan*/  A_EXTOUT_REAR_L ; 
 int /*<<< orphan*/  A_EXTOUT_REAR_R ; 
 int A_FXBUS (int /*<<< orphan*/ ) ; 
 int A_GPR (int) ; 
 scalar_t__ EMU_A_DBG ; 
 int EMU_A_DBG_SINGLE_STEP ; 
 scalar_t__ EMU_A_FXGPREGBASE ; 
 int /*<<< orphan*/  EXTIN_COAX_SPDIF_L ; 
 int /*<<< orphan*/  EXTIN_COAX_SPDIF_R ; 
 int /*<<< orphan*/  FXBUS_PCM_LEFT ; 
 int /*<<< orphan*/  FXBUS_PCM_RIGHT ; 
 int /*<<< orphan*/  audigy_addefxop (struct sc_info*,int,int,int,int,int,int*) ; 
 int /*<<< orphan*/  emu_wrptr (struct sc_info*,int /*<<< orphan*/ ,scalar_t__,int) ; 
 int iACC3 ; 
 int iINTERP ; 
 int iMAC0 ; 

__attribute__((used)) static void
audigy_initefx(struct sc_info *sc)
{
	int i;
	u_int32_t pc = 0;

	/* skip 0, 0, -1, 0 - NOPs */
	for (i = 0; i < 512; i++)
		audigy_addefxop(sc, 0x0f, 0x0c0, 0x0c0, 0x0cf, 0x0c0, &pc);

	for (i = 0; i < 512; i++)
		emu_wrptr(sc, 0, EMU_A_FXGPREGBASE + i, 0x0);

	pc = 16;

	/* stop fx processor */
	emu_wrptr(sc, 0, EMU_A_DBG, EMU_A_DBG_SINGLE_STEP);

	/* Audigy 2 (EMU10K2) DSP Registers:
	   FX Bus
		0x000-0x00f : 16 registers (?)
	   Input
		0x040/0x041 : AC97 Codec (l/r)
		0x042/0x043 : ADC, S/PDIF (l/r)
		0x044/0x045 : Optical S/PDIF in (l/r)
		0x046/0x047 : ?
		0x048/0x049 : Line/Mic 2 (l/r)
		0x04a/0x04b : RCA S/PDIF (l/r)
		0x04c/0x04d : Aux 2 (l/r)
	   Output
		0x060/0x061 : Digital Front (l/r)
		0x062/0x063 : Digital Center/LFE
		0x064/0x065 : AudigyDrive Heaphone (l/r)
		0x066/0x067 : Digital Rear (l/r)
		0x068/0x069 : Analog Front (l/r)
		0x06a/0x06b : Analog Center/LFE
		0x06c/0x06d : ?
		0x06e/0x06f : Analog Rear (l/r)
		0x070/0x071 : AC97 Output (l/r)
		0x072/0x073 : ?
		0x074/0x075 : ?
		0x076/0x077 : ADC Recording Buffer (l/r)
	   Constants
		0x0c0 - 0x0c4 = 0 - 4
		0x0c5 = 0x8, 0x0c6 = 0x10, 0x0c7 = 0x20
		0x0c8 = 0x100, 0x0c9 = 0x10000, 0x0ca = 0x80000
		0x0cb = 0x10000000, 0x0cc = 0x20000000, 0x0cd = 0x40000000
		0x0ce = 0x80000000, 0x0cf = 0x7fffffff, 0x0d0 = 0xffffffff
		0x0d1 = 0xfffffffe, 0x0d2 = 0xc0000000, 0x0d3 = 0x41fbbcdc
		0x0d4 = 0x5a7ef9db, 0x0d5 = 0x00100000, 0x0dc = 0x00000001 (?)
	   Temporary Values
		0x0d6 : Accumulator (?)
		0x0d7 : Condition Register
		0x0d8 : Noise source
		0x0d9 : Noise source
	   Tank Memory Data Registers
		0x200 - 0x2ff
	   Tank Memory Address Registers
		0x300 - 0x3ff
	   General Purpose Registers
		0x400 - 0x5ff
	 */

	/* AC97Output[l/r] = FXBus PCM[l/r] */
	audigy_addefxop(sc, iACC3, A_EXTOUT(A_EXTOUT_AC97_L), A_C_00000000,
			A_C_00000000, A_FXBUS(FXBUS_PCM_LEFT), &pc);
	audigy_addefxop(sc, iACC3, A_EXTOUT(A_EXTOUT_AC97_R), A_C_00000000,
			A_C_00000000, A_FXBUS(FXBUS_PCM_RIGHT), &pc);

	/* GPR[0/1] = RCA S/PDIF[l/r] -- Master volume */
	audigy_addefxop(sc, iACC3, A_GPR(0), A_C_00000000,
			A_C_00000000, A_EXTIN(EXTIN_COAX_SPDIF_L), &pc);
	audigy_addefxop(sc, iACC3, A_GPR(1), A_C_00000000,
			A_C_00000000, A_EXTIN(EXTIN_COAX_SPDIF_R), &pc);

	/* GPR[2] = GPR[0] (Left) / 2 + GPR[1] (Right) / 2 -- Central volume */
	audigy_addefxop(sc, iINTERP, A_GPR(2), A_GPR(1),
			A_C_40000000, A_GPR(0), &pc);

	/* Headphones[l/r] = GPR[0/1] */
	audigy_addefxop(sc, iACC3, A_EXTOUT(A_EXTOUT_HEADPHONE_L),
			A_C_00000000, A_C_00000000, A_GPR(0), &pc);
	audigy_addefxop(sc, iACC3, A_EXTOUT(A_EXTOUT_HEADPHONE_R),
			A_C_00000000, A_C_00000000, A_GPR(1), &pc);

	/* Analog Front[l/r] = GPR[0/1] */
	audigy_addefxop(sc, iACC3, A_EXTOUT(A_EXTOUT_AFRONT_L), A_C_00000000,
			A_C_00000000, A_GPR(0), &pc);
	audigy_addefxop(sc, iACC3, A_EXTOUT(A_EXTOUT_AFRONT_R), A_C_00000000,
			A_C_00000000, A_GPR(1), &pc);

	/* Digital Front[l/r] = GPR[0/1] */
	audigy_addefxop(sc, iACC3, A_EXTOUT(A_EXTOUT_FRONT_L), A_C_00000000,
			A_C_00000000, A_GPR(0), &pc);
	audigy_addefxop(sc, iACC3, A_EXTOUT(A_EXTOUT_FRONT_R), A_C_00000000,
			A_C_00000000, A_GPR(1), &pc);

	/* Center and Subwoofer configuration */
	/* Analog Center = GPR[0] + GPR[2] */
	audigy_addefxop(sc, iACC3, A_EXTOUT(A_EXTOUT_ACENTER), A_C_00000000,
			A_GPR(0), A_GPR(2), &pc);
	/* Analog Sub = GPR[1] + GPR[2] */
	audigy_addefxop(sc, iACC3, A_EXTOUT(A_EXTOUT_ALFE), A_C_00000000,
			A_GPR(1), A_GPR(2), &pc);

	/* Digital Center = GPR[0] + GPR[2] */
	audigy_addefxop(sc, iACC3, A_EXTOUT(A_EXTOUT_CENTER), A_C_00000000,
			A_GPR(0), A_GPR(2), &pc);
	/* Digital Sub = GPR[1] + GPR[2] */
	audigy_addefxop(sc, iACC3, A_EXTOUT(A_EXTOUT_LFE), A_C_00000000,
			A_GPR(1), A_GPR(2), &pc);

#if 0
	/* Analog Rear[l/r] = (GPR[0/1] * RearVolume[l/r]) >> 31 */
	/*   RearVolume = GPR[0x10/0x11] (Will this ever be implemented?) */
	audigy_addefxop(sc, iMAC0, A_EXTOUT(A_EXTOUT_AREAR_L), A_C_00000000,
			A_GPR(16), A_GPR(0), &pc);
	audigy_addefxop(sc, iMAC0, A_EXTOUT(A_EXTOUT_AREAR_R), A_C_00000000,
			A_GPR(17), A_GPR(1), &pc);

	/* Digital Rear[l/r] = (GPR[0/1] * RearVolume[l/r]) >> 31 */
	/*   RearVolume = GPR[0x10/0x11] (Will this ever be implemented?) */
	audigy_addefxop(sc, iMAC0, A_EXTOUT(A_EXTOUT_REAR_L), A_C_00000000,
			A_GPR(16), A_GPR(0), &pc);
	audigy_addefxop(sc, iMAC0, A_EXTOUT(A_EXTOUT_REAR_R), A_C_00000000,
			A_GPR(17), A_GPR(1), &pc);
#else
	/* XXX This is just a copy to the channel, since we do not have
	 *     a patch manager, it is useful for have another output enabled.
	 */

	/* Analog Rear[l/r] = GPR[0/1] */
	audigy_addefxop(sc, iACC3, A_EXTOUT(A_EXTOUT_AREAR_L), A_C_00000000,
			A_C_00000000, A_GPR(0), &pc);
	audigy_addefxop(sc, iACC3, A_EXTOUT(A_EXTOUT_AREAR_R), A_C_00000000,
			A_C_00000000, A_GPR(1), &pc);

	/* Digital Rear[l/r] = GPR[0/1] */
	audigy_addefxop(sc, iACC3, A_EXTOUT(A_EXTOUT_REAR_L), A_C_00000000,
			A_C_00000000, A_GPR(0), &pc);
	audigy_addefxop(sc, iACC3, A_EXTOUT(A_EXTOUT_REAR_R), A_C_00000000,
			A_C_00000000, A_GPR(1), &pc);
#endif

	/* ADC Recording buffer[l/r] = AC97Input[l/r] */
	audigy_addefxop(sc, iACC3, A_EXTOUT(A_EXTOUT_ADC_CAP_L), A_C_00000000,
			A_C_00000000, A_EXTIN(A_EXTIN_AC97_L), &pc);
	audigy_addefxop(sc, iACC3, A_EXTOUT(A_EXTOUT_ADC_CAP_R), A_C_00000000,
			A_C_00000000, A_EXTIN(A_EXTIN_AC97_R), &pc);

	/* resume normal operations */
	emu_wrptr(sc, 0, EMU_A_DBG, 0);
}