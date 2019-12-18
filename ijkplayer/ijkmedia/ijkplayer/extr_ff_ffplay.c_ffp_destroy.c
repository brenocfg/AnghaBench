#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  msg_queue; int /*<<< orphan*/  vf_mutex; int /*<<< orphan*/  af_mutex; int /*<<< orphan*/  meta; int /*<<< orphan*/  pipeline; int /*<<< orphan*/  node_vdec; int /*<<< orphan*/  aout; int /*<<< orphan*/  vout; int /*<<< orphan*/ * is; } ;
typedef  TYPE_1__ FFPlayer ;

/* Variables and functions */
 int /*<<< orphan*/  AV_LOG_WARNING ; 
 int /*<<< orphan*/  SDL_AoutFreeP (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SDL_DestroyMutexP (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SDL_VoutFreeP (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  av_free (TYPE_1__*) ; 
 int /*<<< orphan*/  av_log (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ffp_reset_internal (TYPE_1__*) ; 
 int /*<<< orphan*/  ffpipeline_free_p (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ffpipenode_free_p (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ijkmeta_destroy_p (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  msg_queue_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stream_close (TYPE_1__*) ; 

void ffp_destroy(FFPlayer *ffp)
{
    if (!ffp)
        return;

    if (ffp->is) {
        av_log(NULL, AV_LOG_WARNING, "ffp_destroy_ffplayer: force stream_close()");
        stream_close(ffp);
        ffp->is = NULL;
    }

    SDL_VoutFreeP(&ffp->vout);
    SDL_AoutFreeP(&ffp->aout);
    ffpipenode_free_p(&ffp->node_vdec);
    ffpipeline_free_p(&ffp->pipeline);
    ijkmeta_destroy_p(&ffp->meta);
    ffp_reset_internal(ffp);

    SDL_DestroyMutexP(&ffp->af_mutex);
    SDL_DestroyMutexP(&ffp->vf_mutex);

    msg_queue_destroy(&ffp->msg_queue);


    av_free(ffp);
}