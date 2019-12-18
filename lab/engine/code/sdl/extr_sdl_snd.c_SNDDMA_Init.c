#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_26__   TYPE_8__ ;
typedef  struct TYPE_25__   TYPE_7__ ;
typedef  struct TYPE_24__   TYPE_6__ ;
typedef  struct TYPE_23__   TYPE_5__ ;
typedef  struct TYPE_22__   TYPE_4__ ;
typedef  struct TYPE_21__   TYPE_3__ ;
typedef  struct TYPE_20__   TYPE_2__ ;
typedef  struct TYPE_19__   TYPE_1__ ;
typedef  struct TYPE_18__   TYPE_11__ ;
typedef  struct TYPE_17__   TYPE_10__ ;

/* Type definitions */
typedef  scalar_t__ qboolean ;
typedef  int /*<<< orphan*/  obtained ;
typedef  int /*<<< orphan*/  desired ;
struct TYPE_26__ {scalar_t__ value; } ;
struct TYPE_25__ {int /*<<< orphan*/  integer; } ;
struct TYPE_24__ {scalar_t__ value; } ;
struct TYPE_23__ {int value; } ;
struct TYPE_22__ {int value; } ;
struct TYPE_21__ {scalar_t__ value; } ;
struct TYPE_20__ {int freq; int samples; int channels; void* format; int /*<<< orphan*/  callback; } ;
struct TYPE_19__ {int major; scalar_t__ minor; int patch; } ;
struct TYPE_18__ {scalar_t__ integer; } ;
struct TYPE_17__ {int samplebits; int channels; int samples; int submission_chunk; int speed; int /*<<< orphan*/  buffer; int /*<<< orphan*/  isfloat; } ;
typedef  TYPE_1__ SDL_version ;
typedef  TYPE_2__ SDL_AudioSpec ;

/* Variables and functions */
 void* AUDIO_S16SYS ; 
 void* AUDIO_U8 ; 
 int CVAR_ARCHIVE ; 
 int CVAR_LATCH ; 
 int /*<<< orphan*/  Com_Printf (char*,...) ; 
 void* Cvar_Get (char*,char*,int) ; 
 scalar_t__ Q_stricmp (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  SDL_AUDIO_ALLOW_ANY_CHANGE ; 
 int SDL_AUDIO_BITSIZE (void*) ; 
 int /*<<< orphan*/  SDL_AUDIO_ISFLOAT (void*) ; 
 int /*<<< orphan*/  SDL_FALSE ; 
 int /*<<< orphan*/  SDL_GetCurrentAudioDriver () ; 
 int /*<<< orphan*/  SDL_GetError () ; 
 int /*<<< orphan*/  SDL_GetVersion (TYPE_1__*) ; 
 int /*<<< orphan*/  SDL_INIT_AUDIO ; 
 scalar_t__ SDL_Init (int /*<<< orphan*/ ) ; 
 scalar_t__ SDL_OpenAudioDevice (int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_2__*,TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SDL_PauseAudioDevice (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SDL_QuitSubSystem (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SDL_TRUE ; 
 int /*<<< orphan*/  SDL_zero (TYPE_2__) ; 
 int /*<<< orphan*/  SNDDMA_AudioCallback ; 
 int /*<<< orphan*/  SNDDMA_PrintAudiospec (char*,TYPE_2__*) ; 
 int VOIP_MAX_PACKET_SAMPLES ; 
 int /*<<< orphan*/  calloc (int,int) ; 
 TYPE_11__* cl_useMumble ; 
 TYPE_10__ dma ; 
 scalar_t__ dmapos ; 
 int dmasize ; 
 int /*<<< orphan*/  memset (TYPE_2__*,char,int) ; 
 scalar_t__ qfalse ; 
 scalar_t__ qtrue ; 
 TYPE_8__* s_sdlBits ; 
 TYPE_7__* s_sdlCapture ; 
 TYPE_6__* s_sdlChannels ; 
 TYPE_5__* s_sdlDevSamps ; 
 TYPE_4__* s_sdlMixSamps ; 
 TYPE_3__* s_sdlSpeed ; 
 scalar_t__ sdlCaptureDevice ; 
 float sdlMasterGain ; 
 scalar_t__ sdlPlaybackDevice ; 
 scalar_t__ snd_inited ; 

qboolean SNDDMA_Init(void)
{
	SDL_AudioSpec desired;
	SDL_AudioSpec obtained;
	int tmp;
#ifdef USE_SDL_AUDIO_CAPTURE
	SDL_version sdlVersion;
#endif

	if (snd_inited)
		return qtrue;

	if (!s_sdlBits) {
		s_sdlBits = Cvar_Get("s_sdlBits", "16", CVAR_ARCHIVE);
		s_sdlSpeed = Cvar_Get("s_sdlSpeed", "0", CVAR_ARCHIVE);
		s_sdlChannels = Cvar_Get("s_sdlChannels", "2", CVAR_ARCHIVE);
		s_sdlDevSamps = Cvar_Get("s_sdlDevSamps", "0", CVAR_ARCHIVE);
		s_sdlMixSamps = Cvar_Get("s_sdlMixSamps", "0", CVAR_ARCHIVE);
	}

	Com_Printf( "SDL_Init( SDL_INIT_AUDIO )... " );

	if (SDL_Init(SDL_INIT_AUDIO) != 0)
	{
		Com_Printf( "FAILED (%s)\n", SDL_GetError( ) );
		return qfalse;
	}

	Com_Printf( "OK\n" );

	Com_Printf( "SDL audio driver is \"%s\".\n", SDL_GetCurrentAudioDriver( ) );

	memset(&desired, '\0', sizeof (desired));
	memset(&obtained, '\0', sizeof (obtained));

	tmp = ((int) s_sdlBits->value);
	if ((tmp != 16) && (tmp != 8))
		tmp = 16;

	desired.freq = (int) s_sdlSpeed->value;
	if(!desired.freq) desired.freq = 22050;
	desired.format = ((tmp == 16) ? AUDIO_S16SYS : AUDIO_U8);

	// I dunno if this is the best idea, but I'll give it a try...
	//  should probably check a cvar for this...
	if (s_sdlDevSamps->value)
		desired.samples = s_sdlDevSamps->value;
	else
	{
		// just pick a sane default.
		if (desired.freq <= 11025)
			desired.samples = 256;
		else if (desired.freq <= 22050)
			desired.samples = 512;
		else if (desired.freq <= 44100)
			desired.samples = 1024;
		else
			desired.samples = 2048;  // (*shrug*)
	}

	desired.channels = (int) s_sdlChannels->value;
	desired.callback = SNDDMA_AudioCallback;

	sdlPlaybackDevice = SDL_OpenAudioDevice(NULL, SDL_FALSE, &desired, &obtained, SDL_AUDIO_ALLOW_ANY_CHANGE);
	if (sdlPlaybackDevice == 0)
	{
		Com_Printf("SDL_OpenAudioDevice() failed: %s\n", SDL_GetError());
		SDL_QuitSubSystem(SDL_INIT_AUDIO);
		return qfalse;
	}

	SNDDMA_PrintAudiospec("SDL_AudioSpec", &obtained);

	// dma.samples needs to be big, or id's mixer will just refuse to
	//  work at all; we need to keep it significantly bigger than the
	//  amount of SDL callback samples, and just copy a little each time
	//  the callback runs.
	// 32768 is what the OSS driver filled in here on my system. I don't
	//  know if it's a good value overall, but at least we know it's
	//  reasonable...this is why I let the user override.
	tmp = s_sdlMixSamps->value;
	if (!tmp)
		tmp = (obtained.samples * obtained.channels) * 10;

	if (tmp & (tmp - 1))  // not a power of two? Seems to confuse something.
	{
		int val = 1;
		while (val < tmp)
			val <<= 1;

		tmp = val;
	}

	dmapos = 0;
	dma.samplebits = SDL_AUDIO_BITSIZE(obtained.format);
	dma.isfloat = SDL_AUDIO_ISFLOAT(obtained.format);
	dma.channels = obtained.channels;
	dma.samples = tmp;
	dma.submission_chunk = 1;
	dma.speed = obtained.freq;
	dmasize = (dma.samples * (dma.samplebits/8));
	dma.buffer = calloc(1, dmasize);

#ifdef USE_SDL_AUDIO_CAPTURE
	// !!! FIXME: some of these SDL_OpenAudioDevice() values should be cvars.
	s_sdlCapture = Cvar_Get( "s_sdlCapture", "1", CVAR_ARCHIVE | CVAR_LATCH );
	// !!! FIXME: hopefully pulseaudio capture will be fixed in SDL 2.0.9... https://bugzilla.libsdl.org/show_bug.cgi?id=4087
	SDL_GetVersion(&sdlVersion);
	if (sdlVersion.major == 2 && sdlVersion.minor == 0 && sdlVersion.patch < 9 && Q_stricmp(SDL_GetCurrentAudioDriver(), "pulseaudio") == 0)
	{
		Com_Printf("SDL audio capture support disabled (pulseaudio capture does not work correctly with SDL %d.%d.%d)\n", sdlVersion.major, sdlVersion.minor, sdlVersion.patch);
	}
	else if (!s_sdlCapture->integer)
	{
		Com_Printf("SDL audio capture support disabled by user ('+set s_sdlCapture 1' to enable)\n");
	}
#if USE_MUMBLE
	else if (cl_useMumble->integer)
	{
		Com_Printf("SDL audio capture support disabled for Mumble support\n");
	}
#endif
	else
	{
		/* !!! FIXME: list available devices and let cvar specify one, like OpenAL does */
		SDL_AudioSpec spec;
		SDL_zero(spec);
		spec.freq = 48000;
		spec.format = AUDIO_S16SYS;
		spec.channels = 1;
		spec.samples = VOIP_MAX_PACKET_SAMPLES * 4;
		sdlCaptureDevice = SDL_OpenAudioDevice(NULL, SDL_TRUE, &spec, NULL, 0);
		Com_Printf( "SDL capture device %s.\n",
				    (sdlCaptureDevice == 0) ? "failed to open" : "opened");
	}

	sdlMasterGain = 1.0f;
#endif

	Com_Printf("Starting SDL audio callback...\n");
	SDL_PauseAudioDevice(sdlPlaybackDevice, 0);  // start callback.
	// don't unpause the capture device; we'll do that in StartCapture.

	Com_Printf("SDL audio initialized.\n");
	snd_inited = qtrue;
	return qtrue;
}