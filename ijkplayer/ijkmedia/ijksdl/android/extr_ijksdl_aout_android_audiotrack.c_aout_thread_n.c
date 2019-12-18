#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_7__ {TYPE_2__* opaque; } ;
struct TYPE_5__ {void* userdata; int /*<<< orphan*/  (* callback ) (void*,int /*<<< orphan*/ *,int) ;} ;
struct TYPE_6__ {int need_flush; int /*<<< orphan*/  wakeup_mutex; int /*<<< orphan*/  speed; scalar_t__ speed_changed; int /*<<< orphan*/  right_volume; int /*<<< orphan*/  left_volume; scalar_t__ need_set_volume; scalar_t__ pause_on; int /*<<< orphan*/  abort_request; int /*<<< orphan*/  wakeup_cond; int /*<<< orphan*/ * buffer; TYPE_1__ spec; int /*<<< orphan*/ * atrack; } ;
typedef  int /*<<< orphan*/  (* SDL_AudioCallback ) (void*,int /*<<< orphan*/ *,int) ;
typedef  TYPE_2__ SDL_Aout_Opaque ;
typedef  TYPE_3__ SDL_Aout ;
typedef  int /*<<< orphan*/  SDL_Android_AudioTrack ;
typedef  int /*<<< orphan*/  JNIEnv ;

/* Variables and functions */
 int /*<<< orphan*/  ALOGW (char*,int,int) ; 
 int /*<<< orphan*/  SDL_Android_AudioTrack_flush (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SDL_Android_AudioTrack_free (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SDL_Android_AudioTrack_pause (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SDL_Android_AudioTrack_play (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SDL_Android_AudioTrack_setSpeed (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SDL_Android_AudioTrack_set_volume (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int SDL_Android_AudioTrack_write (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  SDL_CondWaitTimeout (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  SDL_LockMutex (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SDL_SetThreadPriority (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SDL_THREAD_PRIORITY_HIGH ; 
 int /*<<< orphan*/  SDL_UnlockMutex (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int aout_thread_n(JNIEnv *env, SDL_Aout *aout)
{
    SDL_Aout_Opaque *opaque = aout->opaque;
    SDL_Android_AudioTrack *atrack = opaque->atrack;
    SDL_AudioCallback audio_cblk = opaque->spec.callback;
    void *userdata = opaque->spec.userdata;
    uint8_t *buffer = opaque->buffer;
    int copy_size = 256;

    assert(atrack);
    assert(buffer);

    SDL_SetThreadPriority(SDL_THREAD_PRIORITY_HIGH);

    if (!opaque->abort_request && !opaque->pause_on)
        SDL_Android_AudioTrack_play(env, atrack);

    while (!opaque->abort_request) {
        SDL_LockMutex(opaque->wakeup_mutex);
        if (!opaque->abort_request && opaque->pause_on) {
            SDL_Android_AudioTrack_pause(env, atrack);
            while (!opaque->abort_request && opaque->pause_on) {
                SDL_CondWaitTimeout(opaque->wakeup_cond, opaque->wakeup_mutex, 1000);
            }
            if (!opaque->abort_request && !opaque->pause_on) {
                if (opaque->need_flush) {
                    opaque->need_flush = 0;
                    SDL_Android_AudioTrack_flush(env, atrack);
                }
                SDL_Android_AudioTrack_play(env, atrack);
            }
        }
        if (opaque->need_flush) {
            opaque->need_flush = 0;
            SDL_Android_AudioTrack_flush(env, atrack);
        }
        if (opaque->need_set_volume) {
            opaque->need_set_volume = 0;
            SDL_Android_AudioTrack_set_volume(env, atrack, opaque->left_volume, opaque->right_volume);
        }
        if (opaque->speed_changed) {
            opaque->speed_changed = 0;
            SDL_Android_AudioTrack_setSpeed(env, atrack, opaque->speed);
        }
        SDL_UnlockMutex(opaque->wakeup_mutex);

        audio_cblk(userdata, buffer, copy_size);
        if (opaque->need_flush) {
            SDL_Android_AudioTrack_flush(env, atrack);
            opaque->need_flush = false;
        }

        if (opaque->need_flush) {
            opaque->need_flush = 0;
            SDL_Android_AudioTrack_flush(env, atrack);
        } else {
            int written = SDL_Android_AudioTrack_write(env, atrack, buffer, copy_size);
            if (written != copy_size) {
                ALOGW("AudioTrack: not all data copied %d/%d", (int)written, (int)copy_size);
            }
        }

        // TODO: 1 if callback return -1 or 0
    }

    SDL_Android_AudioTrack_free(env, atrack);
    return 0;
}