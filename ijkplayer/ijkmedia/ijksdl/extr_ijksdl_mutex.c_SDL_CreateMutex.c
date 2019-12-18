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
typedef  TYPE_1__ SDL_mutex ;

/* Variables and functions */
 int /*<<< orphan*/  free (TYPE_1__*) ; 
 scalar_t__ mallocz (int) ; 
 scalar_t__ pthread_mutex_init (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

SDL_mutex *SDL_CreateMutex(void)
{
    SDL_mutex *mutex;
    mutex = (SDL_mutex *) mallocz(sizeof(SDL_mutex));
    if (!mutex)
        return NULL;

    if (pthread_mutex_init(&mutex->id, NULL) != 0) {
        free(mutex);
        return NULL;
    }

    return mutex;
}