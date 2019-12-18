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
typedef  int /*<<< orphan*/  uint32_t ;
struct ahci_channel {scalar_t__ disablephy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ATA_SC_DET_DISABLE ; 

__attribute__((used)) static uint32_t
ahci_ch_detval(struct ahci_channel *ch, uint32_t val)
{

	return ch->disablephy ? ATA_SC_DET_DISABLE : val;
}