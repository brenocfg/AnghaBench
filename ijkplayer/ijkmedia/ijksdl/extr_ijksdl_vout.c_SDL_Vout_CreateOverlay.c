#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/ * (* create_overlay ) (int,int,int,TYPE_1__*) ;} ;
typedef  int /*<<< orphan*/  SDL_VoutOverlay ;
typedef  TYPE_1__ SDL_Vout ;

/* Variables and functions */
 int /*<<< orphan*/ * stub1 (int,int,int,TYPE_1__*) ; 

SDL_VoutOverlay *SDL_Vout_CreateOverlay(int width, int height, int frame_format, SDL_Vout *vout)
{
    if (vout && vout->create_overlay)
        return vout->create_overlay(width, height, frame_format, vout);

    return NULL;
}