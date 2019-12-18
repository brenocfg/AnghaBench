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
typedef  int /*<<< orphan*/  SDL_Aout ;
typedef  int /*<<< orphan*/  JNIEnv ;

/* Variables and functions */
 int /*<<< orphan*/  ALOGE (char*) ; 
 scalar_t__ JNI_OK ; 
 scalar_t__ SDL_JNI_SetupThreadEnv (int /*<<< orphan*/ **) ; 
 int aout_thread_n (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int aout_thread(void *arg)
{
    SDL_Aout *aout = arg;
    // SDL_Aout_Opaque *opaque = aout->opaque;
    JNIEnv *env = NULL;

    if (JNI_OK != SDL_JNI_SetupThreadEnv(&env)) {
        ALOGE("aout_thread: SDL_AndroidJni_SetupEnv: failed");
        return -1;
    }

    return aout_thread_n(env, aout);
}