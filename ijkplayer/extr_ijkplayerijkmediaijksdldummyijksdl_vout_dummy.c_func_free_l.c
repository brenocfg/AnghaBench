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
struct TYPE_4__ {int /*<<< orphan*/ * opaque; } ;
typedef  int /*<<< orphan*/  SDL_Vout_Opaque ;
typedef  TYPE_1__ SDL_Vout ;

/* Variables and functions */
 int /*<<< orphan*/  SDL_Vout_FreeInternal (TYPE_1__*) ; 

__attribute__((used)) static void func_free_l(SDL_Vout *vout)
{
    if (!vout)
        return;

    SDL_Vout_Opaque *opaque = vout->opaque;
    if (opaque) {
    }

    SDL_Vout_FreeInternal(vout);
}