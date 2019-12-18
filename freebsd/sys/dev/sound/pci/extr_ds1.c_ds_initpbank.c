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
struct pbank {int Format; int PgLoopEnd; int PgDelta; int PgDeltaEnd; int LpfQ; int LpfK; int LpfKEnd; int EgGain; int EgGainEnd; int LchGain; int LchGainEnd; int RchGain; int RchGainEnd; int Effect1Gain; int Effect1GainEnd; int Effect2Gain; int Effect2GainEnd; int Effect3Gain; int Effect3GainEnd; scalar_t__ LpfD2; scalar_t__ LpfD1; scalar_t__ PgStartFrac; scalar_t__ PgStart; scalar_t__ LoopCount; scalar_t__ NumOfFrames; scalar_t__ Status; scalar_t__ PgLoopFrac; scalar_t__ PgLoop; int /*<<< orphan*/  PgBase; scalar_t__ LoopDefault; } ;
typedef  int /*<<< orphan*/  bus_addr_t ;

/* Variables and functions */

__attribute__((used)) static int
ds_initpbank(volatile struct pbank *pb, int ch, int stereo, int b16, u_int32_t rate, bus_addr_t base, u_int32_t len)
{
	u_int32_t lv[] = {1, 1, 0, 0, 0};
	u_int32_t rv[] = {1, 0, 1, 0, 0};
	u_int32_t e1[] = {0, 0, 0, 0, 0};
	u_int32_t e2[] = {1, 0, 0, 1, 0};
	u_int32_t e3[] = {1, 0, 0, 0, 1};
	int ss, i;
	u_int32_t delta;

	struct {
		int rate, fK, fQ;
	} speedinfo[] = {
		{  100, 0x00570000, 0x35280000},
		{ 2000, 0x06aa0000, 0x34a70000},
		{ 8000, 0x18b20000, 0x32020000},
		{11025, 0x20930000, 0x31770000},
		{16000, 0x2b9a0000, 0x31390000},
		{22050, 0x35a10000, 0x31c90000},
		{32000, 0x3eaa0000, 0x33d00000},
/*		{44100, 0x04646000, 0x370a0000},
*/		{48000, 0x40000000, 0x40000000},
	};

	ss = b16? 1 : 0;
	ss += stereo? 1 : 0;
	delta = (65536 * rate) / 48000;
	i = 0;
	while (i < 7 && speedinfo[i].rate < rate)
		i++;

	pb->Format = stereo? 0x00010000 : 0;
	pb->Format |= b16? 0 : 0x80000000;
	pb->Format |= (stereo && (ch == 2 || ch == 4))? 0x00000001 : 0;
	pb->LoopDefault = 0;
	pb->PgBase = base;
	pb->PgLoop = 0;
	pb->PgLoopEnd = len >> ss;
	pb->PgLoopFrac = 0;
	pb->Status = 0;
	pb->NumOfFrames = 0;
	pb->LoopCount = 0;
	pb->PgStart = 0;
	pb->PgStartFrac = 0;
	pb->PgDelta = pb->PgDeltaEnd = delta << 12;
	pb->LpfQ = speedinfo[i].fQ;
	pb->LpfK = pb->LpfKEnd = speedinfo[i].fK;
	pb->LpfD1 = pb->LpfD2 = 0;
	pb->EgGain = pb->EgGainEnd = 0x40000000;
	pb->LchGain = pb->LchGainEnd = lv[ch] * 0x40000000;
	pb->RchGain = pb->RchGainEnd = rv[ch] * 0x40000000;
	pb->Effect1Gain = pb->Effect1GainEnd = e1[ch] * 0x40000000;
	pb->Effect2Gain = pb->Effect2GainEnd = e2[ch] * 0x40000000;
	pb->Effect3Gain = pb->Effect3GainEnd = e3[ch] * 0x40000000;

	return 0;
}