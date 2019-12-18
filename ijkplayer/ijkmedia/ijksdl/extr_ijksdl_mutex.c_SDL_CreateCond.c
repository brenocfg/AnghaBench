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
struct TYPE_4__ {int /*<<< orphan*/  id; } ;
typedef  TYPE_1__ SDL_cond ;

/* Variables and functions */
 int /*<<< orphan*/  free (TYPE_1__*) ; 
 scalar_t__ mallocz (int) ; 
 scalar_t__ pthread_cond_init (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

SDL_cond *SDL_CreateCond(void)
{
    SDL_cond *cond;
    cond = (SDL_cond *) mallocz(sizeof(SDL_cond));
    if (!cond)
        return NULL;

    if (pthread_cond_init(&cond->id, NULL) != 0) {
        free(cond);
        return NULL;
    }

    return cond;
}