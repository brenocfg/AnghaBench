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

/* Variables and functions */
 int /*<<< orphan*/  DSP_MsaAddrHigh ; 
 int /*<<< orphan*/  DSP_MsaAddrLow ; 
 int /*<<< orphan*/  DSP_MsaDataDSISHigh ; 
 unsigned short InWordDsp (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OutWordDsp (int /*<<< orphan*/ ,unsigned short) ; 
 int /*<<< orphan*/  PRINTK_2 (int /*<<< orphan*/ ,char*,unsigned short) ; 
 int /*<<< orphan*/  PRINTK_3 (int /*<<< orphan*/ ,char*,unsigned short,unsigned long) ; 
 int /*<<< orphan*/  TRACE_3780I ; 
 int /*<<< orphan*/  dsp_lock ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

unsigned short dsp3780I_ReadMsaCfg(unsigned short usDspBaseIO,
                                   unsigned long ulMsaAddr)
{
	unsigned long flags;
	unsigned short val;

	PRINTK_3(TRACE_3780I,
		"3780i::dsp3780I_ReadMsaCfg entry usDspBaseIO %x ulMsaAddr %lx\n",
		usDspBaseIO, ulMsaAddr);

	spin_lock_irqsave(&dsp_lock, flags);
	OutWordDsp(DSP_MsaAddrLow, (unsigned short) ulMsaAddr);
	OutWordDsp(DSP_MsaAddrHigh, (unsigned short) (ulMsaAddr >> 16));
	val = InWordDsp(DSP_MsaDataDSISHigh);
	spin_unlock_irqrestore(&dsp_lock, flags);

	PRINTK_2(TRACE_3780I, "3780i::dsp3780I_ReadMsaCfg exit val %x\n", val);

	return val;
}