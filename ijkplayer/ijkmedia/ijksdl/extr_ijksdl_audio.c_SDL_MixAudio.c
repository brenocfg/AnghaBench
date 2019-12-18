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
typedef  int /*<<< orphan*/  Uint8 ;
typedef  int /*<<< orphan*/  Uint32 ;

/* Variables and functions */

void SDL_MixAudio(Uint8*       dst,
                  const Uint8* src,
                  Uint32       len,
                  int          volume)
{
    // do nothing;
}