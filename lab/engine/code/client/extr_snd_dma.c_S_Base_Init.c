#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  MasterGain; int /*<<< orphan*/  StopCapture; int /*<<< orphan*/  Capture; int /*<<< orphan*/  AvailableCaptureSamples; int /*<<< orphan*/  StartCapture; int /*<<< orphan*/  SoundList; int /*<<< orphan*/  SoundInfo; int /*<<< orphan*/  ClearSoundBuffer; int /*<<< orphan*/  RegisterSound; int /*<<< orphan*/  BeginRegistration; int /*<<< orphan*/  DisableSounds; int /*<<< orphan*/  Update; int /*<<< orphan*/  UpdateEntityPosition; int /*<<< orphan*/  Respatialize; int /*<<< orphan*/  StopLoopingSound; int /*<<< orphan*/  AddRealLoopingSound; int /*<<< orphan*/  AddLoopingSound; int /*<<< orphan*/  ClearLoopingSounds; int /*<<< orphan*/  (* StopAllSounds ) () ;int /*<<< orphan*/  RawSamples; int /*<<< orphan*/  StopBackgroundTrack; int /*<<< orphan*/  StartBackgroundTrack; int /*<<< orphan*/  StartLocalSound; int /*<<< orphan*/  StartSound; int /*<<< orphan*/  Shutdown; } ;
typedef  TYPE_1__ soundInterface_t ;
typedef  int /*<<< orphan*/  sfx_t ;
typedef  scalar_t__ qboolean ;

/* Variables and functions */
 int /*<<< orphan*/  CVAR_ARCHIVE ; 
 int /*<<< orphan*/  CVAR_CHEAT ; 
 int /*<<< orphan*/  Com_Memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 void* Cvar_Get (char*,char*,int /*<<< orphan*/ ) ; 
 int LOOP_HASH ; 
 scalar_t__ SNDDMA_Init () ; 
 int /*<<< orphan*/  S_Base_AddLoopingSound ; 
 int /*<<< orphan*/  S_Base_AddRealLoopingSound ; 
 int /*<<< orphan*/  S_Base_AvailableCaptureSamples ; 
 int /*<<< orphan*/  S_Base_BeginRegistration ; 
 int /*<<< orphan*/  S_Base_Capture ; 
 int /*<<< orphan*/  S_Base_ClearLoopingSounds ; 
 int /*<<< orphan*/  S_Base_ClearSoundBuffer ; 
 int /*<<< orphan*/  S_Base_DisableSounds ; 
 int /*<<< orphan*/  S_Base_MasterGain ; 
 int /*<<< orphan*/  S_Base_RawSamples ; 
 int /*<<< orphan*/  S_Base_RegisterSound ; 
 int /*<<< orphan*/  S_Base_Respatialize ; 
 int /*<<< orphan*/  S_Base_Shutdown ; 
 int /*<<< orphan*/  S_Base_SoundInfo ; 
 int /*<<< orphan*/  S_Base_SoundList ; 
 int /*<<< orphan*/  S_Base_StartBackgroundTrack ; 
 int /*<<< orphan*/  S_Base_StartCapture ; 
 int /*<<< orphan*/  S_Base_StartLocalSound ; 
 int /*<<< orphan*/  S_Base_StartSound ; 
 int /*<<< orphan*/  S_Base_StopAllSounds () ; 
 int /*<<< orphan*/  S_Base_StopBackgroundTrack ; 
 int /*<<< orphan*/  S_Base_StopCapture ; 
 int /*<<< orphan*/  S_Base_StopLoopingSound ; 
 int /*<<< orphan*/  S_Base_Update ; 
 int /*<<< orphan*/  S_Base_UpdateEntityPosition ; 
 scalar_t__ qfalse ; 
 scalar_t__ qtrue ; 
 void* s_mixPreStep ; 
 void* s_mixahead ; 
 scalar_t__ s_paintedtime ; 
 void* s_show ; 
 int s_soundMuted ; 
 int s_soundStarted ; 
 scalar_t__ s_soundtime ; 
 void* s_testsound ; 
 int /*<<< orphan*/  sfxHash ; 

qboolean S_Base_Init( soundInterface_t *si ) {
	qboolean	r;

	if( !si ) {
		return qfalse;
	}

	s_mixahead = Cvar_Get ("s_mixahead", "0.2", CVAR_ARCHIVE);
	s_mixPreStep = Cvar_Get ("s_mixPreStep", "0.05", CVAR_ARCHIVE);
	s_show = Cvar_Get ("s_show", "0", CVAR_CHEAT);
	s_testsound = Cvar_Get ("s_testsound", "0", CVAR_CHEAT);

	r = SNDDMA_Init();

	if ( r ) {
		s_soundStarted = 1;
		s_soundMuted = 1;
//		s_numSfx = 0;

		Com_Memset(sfxHash, 0, sizeof(sfx_t *)*LOOP_HASH);

		s_soundtime = 0;
		s_paintedtime = 0;

		S_Base_StopAllSounds( );
	} else {
		return qfalse;
	}

	si->Shutdown = S_Base_Shutdown;
	si->StartSound = S_Base_StartSound;
	si->StartLocalSound = S_Base_StartLocalSound;
	si->StartBackgroundTrack = S_Base_StartBackgroundTrack;
	si->StopBackgroundTrack = S_Base_StopBackgroundTrack;
	si->RawSamples = S_Base_RawSamples;
	si->StopAllSounds = S_Base_StopAllSounds;
	si->ClearLoopingSounds = S_Base_ClearLoopingSounds;
	si->AddLoopingSound = S_Base_AddLoopingSound;
	si->AddRealLoopingSound = S_Base_AddRealLoopingSound;
	si->StopLoopingSound = S_Base_StopLoopingSound;
	si->Respatialize = S_Base_Respatialize;
	si->UpdateEntityPosition = S_Base_UpdateEntityPosition;
	si->Update = S_Base_Update;
	si->DisableSounds = S_Base_DisableSounds;
	si->BeginRegistration = S_Base_BeginRegistration;
	si->RegisterSound = S_Base_RegisterSound;
	si->ClearSoundBuffer = S_Base_ClearSoundBuffer;
	si->SoundInfo = S_Base_SoundInfo;
	si->SoundList = S_Base_SoundList;

#ifdef USE_VOIP
	si->StartCapture = S_Base_StartCapture;
	si->AvailableCaptureSamples = S_Base_AvailableCaptureSamples;
	si->Capture = S_Base_Capture;
	si->StopCapture = S_Base_StopCapture;
	si->MasterGain = S_Base_MasterGain;
#endif

	return qtrue;
}