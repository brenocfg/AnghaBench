#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int (* msg_loop ) (void*) ;int /*<<< orphan*/  mutex; int /*<<< orphan*/  ffplayer; } ;
typedef  TYPE_1__ IjkMediaPlayer ;

/* Variables and functions */
 int /*<<< orphan*/  ffp_create () ; 
 int /*<<< orphan*/  ijkmp_destroy_p (TYPE_1__**) ; 
 int /*<<< orphan*/  ijkmp_inc_ref (TYPE_1__*) ; 
 scalar_t__ mallocz (int) ; 
 int /*<<< orphan*/  pthread_mutex_init (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

IjkMediaPlayer *ijkmp_create(int (*msg_loop)(void*))
{
    IjkMediaPlayer *mp = (IjkMediaPlayer *) mallocz(sizeof(IjkMediaPlayer));
    if (!mp)
        goto fail;

    mp->ffplayer = ffp_create();
    if (!mp->ffplayer)
        goto fail;

    mp->msg_loop = msg_loop;

    ijkmp_inc_ref(mp);
    pthread_mutex_init(&mp->mutex, NULL);

    return mp;

    fail:
    ijkmp_destroy_p(&mp);
    return NULL;
}