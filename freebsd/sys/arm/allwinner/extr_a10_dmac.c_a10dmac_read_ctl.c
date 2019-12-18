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
struct a10dmac_channel {scalar_t__ ch_type; } ;

/* Variables and functions */
 int /*<<< orphan*/  AWIN_DDMA_CTL_REG ; 
 int /*<<< orphan*/  AWIN_NDMA_CTL_REG ; 
 scalar_t__ CH_NDMA ; 
 int /*<<< orphan*/  DMACH_READ (struct a10dmac_channel*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static uint32_t
a10dmac_read_ctl(struct a10dmac_channel *ch)
{
	if (ch->ch_type == CH_NDMA) {
		return (DMACH_READ(ch, AWIN_NDMA_CTL_REG));
	} else {
		return (DMACH_READ(ch, AWIN_DDMA_CTL_REG));
	}
}