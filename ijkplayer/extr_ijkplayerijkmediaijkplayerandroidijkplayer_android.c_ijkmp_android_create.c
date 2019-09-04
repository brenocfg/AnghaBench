#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_5__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  vout; int /*<<< orphan*/  pipeline; } ;
struct TYPE_6__ {TYPE_5__* ffplayer; } ;
typedef  TYPE_1__ IjkMediaPlayer ;

/* Variables and functions */
 int /*<<< orphan*/  SDL_VoutAndroid_CreateForAndroidSurface () ; 
 int /*<<< orphan*/  ffpipeline_create_from_android (TYPE_5__*) ; 
 int /*<<< orphan*/  ffpipeline_set_vout (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_1__* ijkmp_create (int (*) (void*)) ; 
 int /*<<< orphan*/  ijkmp_dec_ref_p (TYPE_1__**) ; 

IjkMediaPlayer *ijkmp_android_create(int(*msg_loop)(void*))
{
    IjkMediaPlayer *mp = ijkmp_create(msg_loop);
    if (!mp)
        goto fail;

    mp->ffplayer->vout = SDL_VoutAndroid_CreateForAndroidSurface();
    if (!mp->ffplayer->vout)
        goto fail;

    mp->ffplayer->pipeline = ffpipeline_create_from_android(mp->ffplayer);
    if (!mp->ffplayer->pipeline)
        goto fail;

    ffpipeline_set_vout(mp->ffplayer->pipeline, mp->ffplayer->vout);

    return mp;

fail:
    ijkmp_dec_ref_p(&mp);
    return NULL;
}