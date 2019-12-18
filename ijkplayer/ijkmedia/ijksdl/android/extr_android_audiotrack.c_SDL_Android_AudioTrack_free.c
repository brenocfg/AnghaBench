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
struct TYPE_4__ {scalar_t__ thiz; scalar_t__ byte_buffer_capacity; scalar_t__ byte_buffer; } ;
typedef  TYPE_1__ SDL_Android_AudioTrack ;
typedef  int /*<<< orphan*/  JNIEnv ;

/* Variables and functions */
 int /*<<< orphan*/  J4AC_AudioTrack__release (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  J4A_DeleteGlobalRef__p (int /*<<< orphan*/ *,scalar_t__*) ; 
 int /*<<< orphan*/  free (TYPE_1__*) ; 

void SDL_Android_AudioTrack_free(JNIEnv *env, SDL_Android_AudioTrack* atrack)
{
    J4A_DeleteGlobalRef__p(env, &atrack->byte_buffer);
    atrack->byte_buffer_capacity = 0;

    if (atrack->thiz) {
        J4AC_AudioTrack__release(env, atrack->thiz);
        J4A_DeleteGlobalRef__p(env, &atrack->thiz);
    }

    free(atrack);
}