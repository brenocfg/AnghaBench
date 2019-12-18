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
typedef  scalar_t__ uint32_t ;
struct uaudio_chan {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DPRINTF (char*,unsigned int) ; 

int
uaudio_chan_set_param_format(struct uaudio_chan *ch, uint32_t format)
{
	DPRINTF("Selecting format 0x%08x\n", (unsigned int)format);
	return (0);
}