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
struct uaudio_chan {int dummy; } ;

/* Variables and functions */

int
uaudio_chan_set_param_fragments(struct uaudio_chan *ch, uint32_t blocksize,
    uint32_t blockcount)
{
	return (1);
}