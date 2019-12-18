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
struct TYPE_4__ {int /*<<< orphan*/  display_overlay; int /*<<< orphan*/  free_l; } ;
typedef  int /*<<< orphan*/  SDL_Vout_Opaque ;
typedef  TYPE_1__ SDL_Vout ;

/* Variables and functions */
 TYPE_1__* SDL_Vout_CreateInternal (int) ; 
 int /*<<< orphan*/  func_display_overlay ; 
 int /*<<< orphan*/  func_free_l ; 

SDL_Vout *SDL_VoutDummy_Create()
{
    SDL_Vout *vout = SDL_Vout_CreateInternal(sizeof(SDL_Vout_Opaque));
    if (!vout)
        return NULL;

    // SDL_Vout_Opaque *opaque = vout->opaque;

    vout->free_l = func_free_l;
    vout->display_overlay = func_display_overlay;

    return vout;
}