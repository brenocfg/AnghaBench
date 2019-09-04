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
typedef  int /*<<< orphan*/  jobject ;
struct TYPE_2__ {int /*<<< orphan*/  mutex; } ;
typedef  int /*<<< orphan*/  JNIEnv ;
typedef  int /*<<< orphan*/  IjkMediaPlayer ;

/* Variables and functions */
 scalar_t__ J4AC_IjkMediaPlayer__mNativeMediaPlayer__get__catchAll (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  J4AC_IjkMediaPlayer__mNativeMediaPlayer__set__catchAll (int /*<<< orphan*/ *,int /*<<< orphan*/ ,intptr_t) ; 
 TYPE_1__ g_clazz ; 
 int /*<<< orphan*/  ijkmp_dec_ref_p (int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  ijkmp_inc_ref (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static IjkMediaPlayer *jni_set_media_player(JNIEnv* env, jobject thiz, IjkMediaPlayer *mp)
{
    pthread_mutex_lock(&g_clazz.mutex);

    IjkMediaPlayer *old = (IjkMediaPlayer*) (intptr_t) J4AC_IjkMediaPlayer__mNativeMediaPlayer__get__catchAll(env, thiz);
    if (mp) {
        ijkmp_inc_ref(mp);
    }
    J4AC_IjkMediaPlayer__mNativeMediaPlayer__set__catchAll(env, thiz, (intptr_t) mp);

    pthread_mutex_unlock(&g_clazz.mutex);

    // NOTE: ijkmp_dec_ref may block thread
    if (old != NULL ) {
        ijkmp_dec_ref_p(&old);
    }

    return old;
}