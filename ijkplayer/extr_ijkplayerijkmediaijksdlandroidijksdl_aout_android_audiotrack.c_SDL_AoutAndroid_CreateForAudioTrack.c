#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  func_set_playback_rate; int /*<<< orphan*/  func_get_audio_session_id; int /*<<< orphan*/  close_audio; int /*<<< orphan*/  set_volume; int /*<<< orphan*/  flush_audio; int /*<<< orphan*/  pause_audio; int /*<<< orphan*/  open_audio; int /*<<< orphan*/  free_l; int /*<<< orphan*/ * opaque_class; TYPE_1__* opaque; } ;
struct TYPE_5__ {float speed; int /*<<< orphan*/  wakeup_mutex; int /*<<< orphan*/  wakeup_cond; } ;
typedef  TYPE_1__ SDL_Aout_Opaque ;
typedef  TYPE_2__ SDL_Aout ;

/* Variables and functions */
 TYPE_2__* SDL_Aout_CreateInternal (int) ; 
 int /*<<< orphan*/  SDL_CreateCond () ; 
 int /*<<< orphan*/  SDL_CreateMutex () ; 
 int /*<<< orphan*/  aout_close_audio ; 
 int /*<<< orphan*/  aout_flush_audio ; 
 int /*<<< orphan*/  aout_free_l ; 
 int /*<<< orphan*/  aout_get_audio_session_id ; 
 int /*<<< orphan*/  aout_open_audio ; 
 int /*<<< orphan*/  aout_pause_audio ; 
 int /*<<< orphan*/  aout_set_volume ; 
 int /*<<< orphan*/  func_set_playback_rate ; 
 int /*<<< orphan*/  g_audiotrack_class ; 

SDL_Aout *SDL_AoutAndroid_CreateForAudioTrack()
{
    SDL_Aout *aout = SDL_Aout_CreateInternal(sizeof(SDL_Aout_Opaque));
    if (!aout)
        return NULL;

    SDL_Aout_Opaque *opaque = aout->opaque;
    opaque->wakeup_cond  = SDL_CreateCond();
    opaque->wakeup_mutex = SDL_CreateMutex();
    opaque->speed        = 1.0f;

    aout->opaque_class = &g_audiotrack_class;
    aout->free_l       = aout_free_l;
    aout->open_audio   = aout_open_audio;
    aout->pause_audio  = aout_pause_audio;
    aout->flush_audio  = aout_flush_audio;
    aout->set_volume   = aout_set_volume;
    aout->close_audio  = aout_close_audio;
    aout->func_get_audio_session_id = aout_get_audio_session_id;
    aout->func_set_playback_rate    = func_set_playback_rate;

    return aout;
}