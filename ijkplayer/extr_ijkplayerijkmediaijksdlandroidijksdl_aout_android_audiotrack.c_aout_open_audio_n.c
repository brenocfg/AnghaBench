#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct TYPE_13__ {TYPE_2__* opaque; } ;
struct TYPE_11__ {scalar_t__ channels; scalar_t__ format; } ;
struct TYPE_12__ {scalar_t__ buffer_size; int pause_on; int /*<<< orphan*/ * atrack; int /*<<< orphan*/  audio_tid; int /*<<< orphan*/  _audio_tid; scalar_t__ abort_request; int /*<<< orphan*/  audio_session_id; int /*<<< orphan*/  buffer; TYPE_1__ spec; } ;
typedef  TYPE_1__ SDL_AudioSpec ;
typedef  TYPE_2__ SDL_Aout_Opaque ;
typedef  TYPE_3__ SDL_Aout ;
typedef  int /*<<< orphan*/  JNIEnv ;

/* Variables and functions */
 int /*<<< orphan*/  ALOGE (char*) ; 
 int /*<<< orphan*/  ALOGI (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SDLTRACE (char*,int,int) ; 
 int /*<<< orphan*/  SDL_Android_AudioTrack_free (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SDL_Android_AudioTrack_getAudioSessionId (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ SDL_Android_AudioTrack_get_min_buffer_size (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SDL_Android_AudioTrack_get_target_spec (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/ * SDL_Android_AudioTrack_new_from_sdl_spec (int /*<<< orphan*/ *,TYPE_1__ const*) ; 
 int /*<<< orphan*/  SDL_CreateThreadEx (int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_3__*,char*) ; 
 int /*<<< orphan*/  aout_thread ; 
 int /*<<< orphan*/  assert (TYPE_1__ const*) ; 
 int /*<<< orphan*/  malloc (scalar_t__) ; 

__attribute__((used)) static int aout_open_audio_n(JNIEnv *env, SDL_Aout *aout, const SDL_AudioSpec *desired, SDL_AudioSpec *obtained)
{
    assert(desired);
    SDL_Aout_Opaque *opaque = aout->opaque;

    opaque->spec = *desired;
    opaque->atrack = SDL_Android_AudioTrack_new_from_sdl_spec(env, desired);
    if (!opaque->atrack) {
        ALOGE("aout_open_audio_n: failed to new AudioTrcak()");
        return -1;
    }

    opaque->buffer_size = SDL_Android_AudioTrack_get_min_buffer_size(opaque->atrack);
    if (opaque->buffer_size <= 0) {
        ALOGE("aout_open_audio_n: failed to getMinBufferSize()");
        SDL_Android_AudioTrack_free(env, opaque->atrack);
        opaque->atrack = NULL;
        return -1;
    }

    opaque->buffer = malloc(opaque->buffer_size);
    if (!opaque->buffer) {
        ALOGE("aout_open_audio_n: failed to allocate buffer");
        SDL_Android_AudioTrack_free(env, opaque->atrack);
        opaque->atrack = NULL;
        return -1;
    }

    if (obtained) {
        SDL_Android_AudioTrack_get_target_spec(opaque->atrack, obtained);
        SDLTRACE("audio target format fmt:0x%x, channel:0x%x", (int)obtained->format, (int)obtained->channels);
    }

    opaque->audio_session_id = SDL_Android_AudioTrack_getAudioSessionId(env, opaque->atrack);
    ALOGI("audio_session_id = %d\n", opaque->audio_session_id);

    opaque->pause_on = 1;
    opaque->abort_request = 0;
    opaque->audio_tid = SDL_CreateThreadEx(&opaque->_audio_tid, aout_thread, aout, "ff_aout_android");
    if (!opaque->audio_tid) {
        ALOGE("aout_open_audio_n: failed to create audio thread");
        SDL_Android_AudioTrack_free(env, opaque->atrack);
        opaque->atrack = NULL;
        return -1;
    }

    return 0;
}