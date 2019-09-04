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
typedef  enum AVLockOp { ____Placeholder_AVLockOp } AVLockOp ;

/* Variables and functions */
#define  AV_LOCK_CREATE 131 
#define  AV_LOCK_DESTROY 130 
#define  AV_LOCK_OBTAIN 129 
#define  AV_LOCK_RELEASE 128 
 int /*<<< orphan*/  AV_LOG_FATAL ; 
 void* SDL_CreateMutex () ; 
 int /*<<< orphan*/  SDL_DestroyMutex (void*) ; 
 int /*<<< orphan*/  SDL_GetError () ; 
 int /*<<< orphan*/  SDL_LockMutex (void*) ; 
 int /*<<< orphan*/  SDL_UnlockMutex (void*) ; 
 int /*<<< orphan*/  av_log (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int lockmgr(void **mtx, enum AVLockOp op)
{
    switch (op) {
    case AV_LOCK_CREATE:
        *mtx = SDL_CreateMutex();
        if (!*mtx) {
            av_log(NULL, AV_LOG_FATAL, "SDL_CreateMutex(): %s\n", SDL_GetError());
            return 1;
        }
        return 0;
    case AV_LOCK_OBTAIN:
        return !!SDL_LockMutex(*mtx);
    case AV_LOCK_RELEASE:
        return !!SDL_UnlockMutex(*mtx);
    case AV_LOCK_DESTROY:
        SDL_DestroyMutex(*mtx);
        return 0;
    }
    return 1;
}