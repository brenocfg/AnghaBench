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
typedef  int uint32_t ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int pcm_getflags (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pcm_setflags (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
uaudio_pcm_setflags(device_t dev, uint32_t flags)
{
	pcm_setflags(dev, pcm_getflags(dev) | flags);
}