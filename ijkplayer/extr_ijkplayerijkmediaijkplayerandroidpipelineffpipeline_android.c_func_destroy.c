#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {TYPE_1__* opaque; } ;
struct TYPE_4__ {int /*<<< orphan*/  jsurface; int /*<<< orphan*/  surface_mutex; } ;
typedef  int /*<<< orphan*/  JNIEnv ;
typedef  TYPE_1__ IJKFF_Pipeline_Opaque ;
typedef  TYPE_2__ IJKFF_Pipeline ;

/* Variables and functions */
 int /*<<< orphan*/  ALOGE (char*) ; 
 scalar_t__ JNI_OK ; 
 int /*<<< orphan*/  SDL_DestroyMutexP (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SDL_JNI_DeleteGlobalRefP (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ SDL_JNI_SetupThreadEnv (int /*<<< orphan*/ **) ; 

__attribute__((used)) static void func_destroy(IJKFF_Pipeline *pipeline)
{
    IJKFF_Pipeline_Opaque *opaque = pipeline->opaque;
    JNIEnv *env = NULL;

    SDL_DestroyMutexP(&opaque->surface_mutex);

    if (JNI_OK != SDL_JNI_SetupThreadEnv(&env)) {
        ALOGE("amediacodec-pipeline:destroy: SetupThreadEnv failed\n");
        goto fail;
    }

    SDL_JNI_DeleteGlobalRefP(env, &opaque->jsurface);
fail:
    return;
}