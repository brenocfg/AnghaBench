#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int object_serial; } ;
typedef  TYPE_1__ SDL_AMediaCodec ;

/* Variables and functions */

int SDL_AMediaCodec_getSerial(SDL_AMediaCodec* acodec)
{
    if (!acodec)
        return 0;
    return acodec->object_serial;
}