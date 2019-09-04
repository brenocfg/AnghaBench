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
struct TYPE_4__ {int /*<<< orphan*/  mutex; } ;
typedef  TYPE_1__ IjkMediaMeta ;

/* Variables and functions */
 int /*<<< orphan*/  SDL_CreateMutex () ; 
 scalar_t__ calloc (int,int) ; 
 int /*<<< orphan*/  ijkmeta_destroy (TYPE_1__*) ; 

IjkMediaMeta *ijkmeta_create()
{
    IjkMediaMeta *meta = (IjkMediaMeta *)calloc(1, sizeof(IjkMediaMeta));
    if (!meta)
        return NULL;

    meta->mutex = SDL_CreateMutex();
    if (!meta->mutex)
        goto fail;

    return meta;
fail:
    ijkmeta_destroy(meta);
    return NULL;
}