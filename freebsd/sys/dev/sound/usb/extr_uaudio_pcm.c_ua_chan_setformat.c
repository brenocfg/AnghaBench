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
typedef  int /*<<< orphan*/  kobj_t ;

/* Variables and functions */
 int uaudio_chan_set_param_format (void*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
ua_chan_setformat(kobj_t obj, void *data, uint32_t format)
{
	/*
	 * At this point, no need to query as we
	 * shouldn't select an unsorted format
	 */
	return (uaudio_chan_set_param_format(data, format));
}