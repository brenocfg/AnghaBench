#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  data; int /*<<< orphan*/  (* func ) (int /*<<< orphan*/ ) ;int /*<<< orphan*/  retval; int /*<<< orphan*/  name; } ;
typedef  TYPE_1__ SDL_Thread ;

/* Variables and functions */
 int /*<<< orphan*/  ALOGI (char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SDL_JNI_DetachThreadEnv () ; 
 scalar_t__ gettid () ; 
 int /*<<< orphan*/  pthread_self () ; 
 int /*<<< orphan*/  pthread_setname_np (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void *SDL_RunThread(void *data)
{
    SDL_Thread *thread = data;
    ALOGI("SDL_RunThread: [%d] %s\n", (int)gettid(), thread->name);
    pthread_setname_np(pthread_self(), thread->name);
    thread->retval = thread->func(thread->data);
#ifdef __ANDROID__
    SDL_JNI_DetachThreadEnv();
#endif
    return NULL;
}