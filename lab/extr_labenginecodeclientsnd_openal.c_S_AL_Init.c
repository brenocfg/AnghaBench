#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  soundInterface_t ;
typedef  int /*<<< orphan*/  qboolean ;

/* Variables and functions */
 int /*<<< orphan*/  qfalse ; 

qboolean S_AL_Init( soundInterface_t *si )
{
#ifdef USE_OPENAL
	const char* device = NULL;
	const char* inputdevice = NULL;
	int i;

	if( !si ) {
		return qfalse;
	}

	for (i = 0; i < MAX_RAW_STREAMS; i++) {
		streamSourceHandles[i] = -1;
		streamPlaying[i] = qfalse;
		streamSources[i] = 0;
		streamNumBuffers[i] = 0;
		streamBufIndex[i] = 0;
	}

	// New console variables
	s_alPrecache = Cvar_Get( "s_alPrecache", "1", CVAR_ARCHIVE );
	s_alGain = Cvar_Get( "s_alGain", "1.0", CVAR_ARCHIVE );
	s_alSources = Cvar_Get( "s_alSources", "96", CVAR_ARCHIVE );
	s_alDopplerFactor = Cvar_Get( "s_alDopplerFactor", "1.0", CVAR_ARCHIVE );
	s_alDopplerSpeed = Cvar_Get( "s_alDopplerSpeed", "9000", CVAR_ARCHIVE );
	s_alMinDistance = Cvar_Get( "s_alMinDistance", "120", CVAR_CHEAT );
	s_alMaxDistance = Cvar_Get("s_alMaxDistance", "1024", CVAR_CHEAT);
	s_alRolloff = Cvar_Get( "s_alRolloff", "2", CVAR_CHEAT);
	s_alGraceDistance = Cvar_Get("s_alGraceDistance", "512", CVAR_CHEAT);

	s_alDriver = Cvar_Get( "s_alDriver", ALDRIVER_DEFAULT, CVAR_ARCHIVE | CVAR_LATCH | CVAR_PROTECTED );

	s_alInputDevice = Cvar_Get( "s_alInputDevice", "", CVAR_ARCHIVE | CVAR_LATCH );
	s_alDevice = Cvar_Get("s_alDevice", "", CVAR_ARCHIVE | CVAR_LATCH);

	// Load QAL
	if( !QAL_Init( s_alDriver->string ) )
	{
		Com_Printf( "Failed to load library: \"%s\".\n", s_alDriver->string );
		if( !Q_stricmp( s_alDriver->string, ALDRIVER_DEFAULT ) || !QAL_Init( ALDRIVER_DEFAULT ) ) {
			return qfalse;
		}
	}

	device = s_alDevice->string;
	if(device && !*device)
		device = NULL;

	inputdevice = s_alInputDevice->string;
	if(inputdevice && !*inputdevice)
		inputdevice = NULL;


	// Device enumeration support
	enumeration_all_ext = qalcIsExtensionPresent(NULL, "ALC_ENUMERATE_ALL_EXT");
	enumeration_ext = qalcIsExtensionPresent(NULL, "ALC_ENUMERATION_EXT");

	if(enumeration_ext || enumeration_all_ext)
	{
		char devicenames[16384] = "";
		const char *devicelist;
#ifdef _WIN32
		const char *defaultdevice;
#endif
		int curlen;

		// get all available devices + the default device name.
		if(enumeration_all_ext)
		{
			devicelist = qalcGetString(NULL, ALC_ALL_DEVICES_SPECIFIER);
#ifdef _WIN32
			defaultdevice = qalcGetString(NULL, ALC_DEFAULT_ALL_DEVICES_SPECIFIER);
#endif
		}
		else
		{
			// We don't have ALC_ENUMERATE_ALL_EXT but normal enumeration.
			devicelist = qalcGetString(NULL, ALC_DEVICE_SPECIFIER);
#ifdef _WIN32
			defaultdevice = qalcGetString(NULL, ALC_DEFAULT_DEVICE_SPECIFIER);
#endif
			enumeration_ext = qtrue;
		}

#ifdef _WIN32
		// check whether the default device is generic hardware. If it is, change to
		// Generic Software as that one works more reliably with various sound systems.
		// If it's not, use OpenAL's default selection as we don't want to ignore
		// native hardware acceleration.
		if(!device && defaultdevice && !strcmp(defaultdevice, "Generic Hardware"))
			device = "Generic Software";
#endif

		// dump a list of available devices to a cvar for the user to see.

		if(devicelist)
		{
			while((curlen = strlen(devicelist)))
			{
				Q_strcat(devicenames, sizeof(devicenames), devicelist);
				Q_strcat(devicenames, sizeof(devicenames), "\n");

				devicelist += curlen + 1;
			}
		}

		s_alAvailableDevices = Cvar_Get("s_alAvailableDevices", devicenames, CVAR_ROM | CVAR_NORESTART);
	}

	alDevice = qalcOpenDevice(device);
	if( !alDevice && device )
	{
		Com_Printf( "Failed to open OpenAL device '%s', trying default.\n", device );
		alDevice = qalcOpenDevice(NULL);
	}

	if( !alDevice )
	{
		QAL_Shutdown( );
		Com_Printf( "Failed to open OpenAL device.\n" );
		return qfalse;
	}

	// Create OpenAL context
	alContext = qalcCreateContext( alDevice, NULL );
	if( !alContext )
	{
		QAL_Shutdown( );
		qalcCloseDevice( alDevice );
		Com_Printf( "Failed to create OpenAL context.\n" );
		return qfalse;
	}
	qalcMakeContextCurrent( alContext );

	// Initialize sources, buffers, music
	S_AL_BufferInit( );
	S_AL_SrcInit( );

	// Set up OpenAL parameters (doppler, etc)
	qalDistanceModel(AL_INVERSE_DISTANCE_CLAMPED);
	qalDopplerFactor( s_alDopplerFactor->value );
	qalSpeedOfSound( s_alDopplerSpeed->value );

#ifdef USE_VOIP
	// !!! FIXME: some of these alcCaptureOpenDevice() values should be cvars.
	// !!! FIXME: add support for capture device enumeration.
	// !!! FIXME: add some better error reporting.
	s_alCapture = Cvar_Get( "s_alCapture", "1", CVAR_ARCHIVE | CVAR_LATCH );
	if (!s_alCapture->integer)
	{
		Com_Printf("OpenAL capture support disabled by user ('+set s_alCapture 1' to enable)\n");
	}
#if USE_MUMBLE
	else if (cl_useMumble->integer)
	{
		Com_Printf("OpenAL capture support disabled for Mumble support\n");
	}
#endif
	else
	{
#ifdef __APPLE__
		// !!! FIXME: Apple has a 1.1-compliant OpenAL, which includes
		// !!! FIXME:  capture support, but they don't list it in the
		// !!! FIXME:  extension string. We need to check the version string,
		// !!! FIXME:  then the extension string, but that's too much trouble,
		// !!! FIXME:  so we'll just check the function pointer for now.
		if (qalcCaptureOpenDevice == NULL)
#else
		if (!qalcIsExtensionPresent(NULL, "ALC_EXT_capture"))
#endif
		{
			Com_Printf("No ALC_EXT_capture support, can't record audio.\n");
		}
		else
		{
			char inputdevicenames[16384] = "";
			const char *inputdevicelist;
			const char *defaultinputdevice;
			int curlen;

			capture_ext = qtrue;

			// get all available input devices + the default input device name.
			inputdevicelist = qalcGetString(NULL, ALC_CAPTURE_DEVICE_SPECIFIER);
			defaultinputdevice = qalcGetString(NULL, ALC_CAPTURE_DEFAULT_DEVICE_SPECIFIER);

			// dump a list of available devices to a cvar for the user to see.
			if (inputdevicelist)
			{
				while((curlen = strlen(inputdevicelist)))
				{
					Q_strcat(inputdevicenames, sizeof(inputdevicenames), inputdevicelist);
					Q_strcat(inputdevicenames, sizeof(inputdevicenames), "\n");
					inputdevicelist += curlen + 1;
				}
			}

			s_alAvailableInputDevices = Cvar_Get("s_alAvailableInputDevices", inputdevicenames, CVAR_ROM | CVAR_NORESTART);

			Com_Printf("OpenAL default capture device is '%s'\n", defaultinputdevice ? defaultinputdevice : "none");
			alCaptureDevice = qalcCaptureOpenDevice(inputdevice, 48000, AL_FORMAT_MONO16, VOIP_MAX_PACKET_SAMPLES*4);
			if( !alCaptureDevice && inputdevice )
			{
				Com_Printf( "Failed to open OpenAL Input device '%s', trying default.\n", inputdevice );
				alCaptureDevice = qalcCaptureOpenDevice(NULL, 48000, AL_FORMAT_MONO16, VOIP_MAX_PACKET_SAMPLES*4);
			}
			Com_Printf( "OpenAL capture device %s.\n",
				    (alCaptureDevice == NULL) ? "failed to open" : "opened");
		}
	}
#endif

	si->Shutdown = S_AL_Shutdown;
	si->StartSound = S_AL_StartSound;
	si->StartLocalSound = S_AL_StartLocalSound;
	si->StartBackgroundTrack = S_AL_StartBackgroundTrack;
	si->StopBackgroundTrack = S_AL_StopBackgroundTrack;
	si->RawSamples = S_AL_RawSamples;
	si->StopAllSounds = S_AL_StopAllSounds;
	si->ClearLoopingSounds = S_AL_ClearLoopingSounds;
	si->AddLoopingSound = S_AL_AddLoopingSound;
	si->AddRealLoopingSound = S_AL_AddRealLoopingSound;
	si->StopLoopingSound = S_AL_StopLoopingSound;
	si->Respatialize = S_AL_Respatialize;
	si->UpdateEntityPosition = S_AL_UpdateEntityPosition;
	si->Update = S_AL_Update;
	si->DisableSounds = S_AL_DisableSounds;
	si->BeginRegistration = S_AL_BeginRegistration;
	si->RegisterSound = S_AL_RegisterSound;
	si->ClearSoundBuffer = S_AL_ClearSoundBuffer;
	si->SoundInfo = S_AL_SoundInfo;
	si->SoundList = S_AL_SoundList;

#ifdef USE_VOIP
	si->StartCapture = S_AL_StartCapture;
	si->AvailableCaptureSamples = S_AL_AvailableCaptureSamples;
	si->Capture = S_AL_Capture;
	si->StopCapture = S_AL_StopCapture;
	si->MasterGain = S_AL_MasterGain;
#endif

	return qtrue;
#else
	return qfalse;
#endif
}