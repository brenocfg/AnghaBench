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
typedef  int u64 ;
typedef  int u32 ;
struct fw_ohci {int mc_channels; } ;

/* Variables and functions */
 int /*<<< orphan*/  OHCI1394_IRMultiChanMaskHiClear ; 
 int /*<<< orphan*/  OHCI1394_IRMultiChanMaskHiSet ; 
 int /*<<< orphan*/  OHCI1394_IRMultiChanMaskLoClear ; 
 int /*<<< orphan*/  OHCI1394_IRMultiChanMaskLoSet ; 
 int /*<<< orphan*/  reg_write (struct fw_ohci*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void set_multichannel_mask(struct fw_ohci *ohci, u64 channels)
{
	u32 hi = channels >> 32, lo = channels;

	reg_write(ohci, OHCI1394_IRMultiChanMaskHiClear, ~hi);
	reg_write(ohci, OHCI1394_IRMultiChanMaskLoClear, ~lo);
	reg_write(ohci, OHCI1394_IRMultiChanMaskHiSet, hi);
	reg_write(ohci, OHCI1394_IRMultiChanMaskLoSet, lo);
	ohci->mc_channels = channels;
}