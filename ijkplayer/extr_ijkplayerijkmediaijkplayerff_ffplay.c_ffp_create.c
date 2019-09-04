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
struct TYPE_5__ {int /*<<< orphan*/  meta; int /*<<< orphan*/ * av_class; void* vf_mutex; void* af_mutex; int /*<<< orphan*/  msg_queue; } ;
typedef  TYPE_1__ FFPlayer ;

/* Variables and functions */
 int /*<<< orphan*/  AV_LOG_INFO ; 
 void* SDL_CreateMutex () ; 
 int /*<<< orphan*/  av_log (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 scalar_t__ av_mallocz (int) ; 
 int /*<<< orphan*/  av_opt_set_defaults (TYPE_1__*) ; 
 int /*<<< orphan*/  av_version_info () ; 
 int /*<<< orphan*/  ffp_context_class ; 
 int /*<<< orphan*/  ffp_reset_internal (TYPE_1__*) ; 
 int /*<<< orphan*/  ijk_version_info () ; 
 int /*<<< orphan*/  ijkmeta_create () ; 
 int /*<<< orphan*/  msg_queue_init (int /*<<< orphan*/ *) ; 

FFPlayer *ffp_create()
{
    av_log(NULL, AV_LOG_INFO, "av_version_info: %s\n", av_version_info());
    av_log(NULL, AV_LOG_INFO, "ijk_version_info: %s\n", ijk_version_info());

    FFPlayer* ffp = (FFPlayer*) av_mallocz(sizeof(FFPlayer));
    if (!ffp)
        return NULL;

    msg_queue_init(&ffp->msg_queue);
    ffp->af_mutex = SDL_CreateMutex();
    ffp->vf_mutex = SDL_CreateMutex();

    ffp_reset_internal(ffp);
    ffp->av_class = &ffp_context_class;
    ffp->meta = ijkmeta_create();

    av_opt_set_defaults(ffp);

    return ffp;
}