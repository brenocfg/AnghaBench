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
typedef  int /*<<< orphan*/  Uint32 ;
struct TYPE_3__ {int /*<<< orphan*/  overlay_format; } ;
typedef  TYPE_1__ SDL_Vout ;

/* Variables and functions */

int SDL_VoutSetOverlayFormat(SDL_Vout *vout, Uint32 overlay_format)
{
    if (!vout)
        return -1;

    vout->overlay_format = overlay_format;
    return 0;
}