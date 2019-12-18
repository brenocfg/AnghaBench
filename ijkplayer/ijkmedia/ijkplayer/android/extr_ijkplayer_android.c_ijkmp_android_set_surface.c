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
typedef  scalar_t__ jobject ;
struct TYPE_4__ {int /*<<< orphan*/  mutex; } ;
typedef  int /*<<< orphan*/  JNIEnv ;
typedef  TYPE_1__ IjkMediaPlayer ;

/* Variables and functions */
 int /*<<< orphan*/  MPTRACE (char*,void*) ; 
 int /*<<< orphan*/  ijkmp_android_set_surface_l (int /*<<< orphan*/ *,TYPE_1__*,scalar_t__) ; 
 int /*<<< orphan*/  pthread_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_unlock (int /*<<< orphan*/ *) ; 

void ijkmp_android_set_surface(JNIEnv *env, IjkMediaPlayer *mp, jobject android_surface)
{
    if (!mp)
        return;

    MPTRACE("ijkmp_set_android_surface(surface=%p)", (void*)android_surface);
    pthread_mutex_lock(&mp->mutex);
    ijkmp_android_set_surface_l(env, mp, android_surface);
    pthread_mutex_unlock(&mp->mutex);
    MPTRACE("ijkmp_set_android_surface(surface=%p)=void", (void*)android_surface);
}