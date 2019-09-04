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
struct TYPE_5__ {int /*<<< orphan*/  mutex; TYPE_1__* ffplayer; } ;
struct TYPE_4__ {scalar_t__ pipeline; } ;
typedef  int /*<<< orphan*/  JNIEnv ;
typedef  TYPE_2__ IjkMediaPlayer ;

/* Variables and functions */
 int /*<<< orphan*/  MPTRACE (char*,float,float) ; 
 int /*<<< orphan*/  ffpipeline_set_volume (scalar_t__,float,float) ; 
 int /*<<< orphan*/  pthread_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_unlock (int /*<<< orphan*/ *) ; 

void ijkmp_android_set_volume(JNIEnv *env, IjkMediaPlayer *mp, float left, float right)
{
    if (!mp)
        return;

    MPTRACE("ijkmp_android_set_volume(%f, %f)", left, right);
    pthread_mutex_lock(&mp->mutex);

    if (mp && mp->ffplayer && mp->ffplayer->pipeline) {
        ffpipeline_set_volume(mp->ffplayer->pipeline, left, right);
    }

    pthread_mutex_unlock(&mp->mutex);
    MPTRACE("ijkmp_android_set_volume(%f, %f)=void", left, right);
}