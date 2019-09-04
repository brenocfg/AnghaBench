#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {int /*<<< orphan*/  (* SetPlayState ) (TYPE_5__**,int /*<<< orphan*/ ) ;} ;
struct TYPE_10__ {int /*<<< orphan*/  (* Clear ) (TYPE_4__**) ;} ;
struct TYPE_9__ {int /*<<< orphan*/  (* Destroy ) (TYPE_3__**) ;} ;
struct TYPE_8__ {TYPE_1__* opaque; } ;
struct TYPE_7__ {int abort_request; int /*<<< orphan*/  buffer; TYPE_3__** slPlayerObject; TYPE_5__** slPlayItf; int /*<<< orphan*/ * slVolumeItf; TYPE_4__** slBufferQueueItf; int /*<<< orphan*/ * audio_tid; int /*<<< orphan*/  wakeup_mutex; int /*<<< orphan*/  wakeup_cond; } ;
typedef  TYPE_1__ SDL_Aout_Opaque ;
typedef  TYPE_2__ SDL_Aout ;

/* Variables and functions */
 int /*<<< orphan*/  SDLTRACE (char*) ; 
 int /*<<< orphan*/  SDL_CondSignal (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SDL_LockMutex (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SDL_UnlockMutex (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SDL_WaitThread (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SL_PLAYSTATE_STOPPED ; 
 int /*<<< orphan*/  freep (void**) ; 
 int /*<<< orphan*/  stub1 (TYPE_5__**,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (TYPE_4__**) ; 
 int /*<<< orphan*/  stub3 (TYPE_3__**) ; 

__attribute__((used)) static void aout_close_audio(SDL_Aout *aout)
{
    SDLTRACE("aout_close_audio()\n");
    SDL_Aout_Opaque *opaque = aout->opaque;
    if (!opaque)
        return;

    SDL_LockMutex(opaque->wakeup_mutex);
    opaque->abort_request = true;
    SDL_CondSignal(opaque->wakeup_cond);
    SDL_UnlockMutex(opaque->wakeup_mutex);

    SDL_WaitThread(opaque->audio_tid, NULL);
    opaque->audio_tid = NULL;

    if (opaque->slPlayItf)
        (*opaque->slPlayItf)->SetPlayState(opaque->slPlayItf, SL_PLAYSTATE_STOPPED);
    if (opaque->slBufferQueueItf)
        (*opaque->slBufferQueueItf)->Clear(opaque->slBufferQueueItf);

    if (opaque->slBufferQueueItf)
        opaque->slBufferQueueItf = NULL;
    if (opaque->slVolumeItf)
        opaque->slVolumeItf      = NULL;
    if (opaque->slPlayItf)
        opaque->slPlayItf        = NULL;

    if (opaque->slPlayerObject) {
        (*opaque->slPlayerObject)->Destroy(opaque->slPlayerObject);
        opaque->slPlayerObject = NULL;
    }

    freep((void **)&opaque->buffer);
}