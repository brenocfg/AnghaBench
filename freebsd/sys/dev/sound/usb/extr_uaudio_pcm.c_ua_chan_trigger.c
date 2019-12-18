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
typedef  int /*<<< orphan*/  kobj_t ;

/* Variables and functions */
 scalar_t__ PCMTRIG_COMMON (int) ; 
 int PCMTRIG_START ; 
 int /*<<< orphan*/  uaudio_chan_start (void*) ; 
 int /*<<< orphan*/  uaudio_chan_stop (void*) ; 

__attribute__((used)) static int
ua_chan_trigger(kobj_t obj, void *data, int go)
{
	if (PCMTRIG_COMMON(go)) {
		if (go == PCMTRIG_START) {
			uaudio_chan_start(data);
		} else {
			uaudio_chan_stop(data);
		}
	}
	return (0);
}