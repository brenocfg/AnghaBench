#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_23__   TYPE_9__ ;
typedef  struct TYPE_22__   TYPE_8__ ;
typedef  struct TYPE_21__   TYPE_7__ ;
typedef  struct TYPE_20__   TYPE_6__ ;
typedef  struct TYPE_19__   TYPE_5__ ;
typedef  struct TYPE_18__   TYPE_4__ ;
typedef  struct TYPE_17__   TYPE_3__ ;
typedef  struct TYPE_16__   TYPE_2__ ;
typedef  struct TYPE_15__   TYPE_1__ ;
typedef  struct TYPE_14__   TYPE_11__ ;
typedef  struct TYPE_13__   TYPE_10__ ;

/* Type definitions */
typedef  char keyNum_t ;
struct TYPE_23__ {int /*<<< orphan*/  down; } ;
struct TYPE_20__ {int data1; int data2; int /*<<< orphan*/  event; } ;
struct TYPE_19__ {int /*<<< orphan*/  y; } ;
struct TYPE_18__ {int const button; } ;
struct TYPE_17__ {int xrel; int /*<<< orphan*/  yrel; } ;
struct TYPE_16__ {char* text; } ;
struct TYPE_15__ {int /*<<< orphan*/  keysym; int /*<<< orphan*/  repeat; } ;
struct TYPE_22__ {int type; TYPE_6__ window; TYPE_5__ wheel; TYPE_4__ button; TYPE_3__ motion; TYPE_2__ text; TYPE_1__ key; } ;
struct TYPE_21__ {int vidWidth; int vidHeight; int /*<<< orphan*/  isFullscreen; } ;
struct TYPE_14__ {TYPE_7__ glconfig; } ;
struct TYPE_13__ {int /*<<< orphan*/  integer; } ;
typedef  TYPE_8__ SDL_Event ;

/* Variables and functions */
 int CTRL (char) ; 
 int /*<<< orphan*/  Cbuf_ExecuteText (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  Com_DPrintf (char*,unsigned int) ; 
 int /*<<< orphan*/  Com_QueueEvent (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Cvar_Set (char*,char*) ; 
 int /*<<< orphan*/  Cvar_SetValue (char*,int) ; 
 int /*<<< orphan*/  EXEC_NOW ; 
 int /*<<< orphan*/  IN_InitJoystick () ; 
 int /*<<< orphan*/  IN_IsConsoleKey (int /*<<< orphan*/ ,int) ; 
 char IN_TranslateSDLToQ3Key (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  K_AUX1 ; 
 char K_BACKSPACE ; 
 char K_CONSOLE ; 
 size_t K_CTRL ; 
 int K_MOUSE1 ; 
 int K_MOUSE2 ; 
 int K_MOUSE3 ; 
 int K_MOUSE4 ; 
 int K_MOUSE5 ; 
 int K_MWHEELDOWN ; 
 int K_MWHEELUP ; 
 int /*<<< orphan*/  Key_GetCatcher () ; 
#define  SDL_BUTTON_LEFT 149 
#define  SDL_BUTTON_MIDDLE 148 
#define  SDL_BUTTON_RIGHT 147 
#define  SDL_BUTTON_X1 146 
#define  SDL_BUTTON_X2 145 
#define  SDL_CONTROLLERDEVICEADDED 144 
#define  SDL_CONTROLLERDEVICEREMOVED 143 
 int /*<<< orphan*/  SDL_INIT_VIDEO ; 
#define  SDL_KEYDOWN 142 
#define  SDL_KEYUP 141 
#define  SDL_MOUSEBUTTONDOWN 140 
#define  SDL_MOUSEBUTTONUP 139 
#define  SDL_MOUSEMOTION 138 
#define  SDL_MOUSEWHEEL 137 
 scalar_t__ SDL_PollEvent (TYPE_8__*) ; 
#define  SDL_QUIT 136 
#define  SDL_TEXTINPUT 135 
#define  SDL_WINDOWEVENT 134 
#define  SDL_WINDOWEVENT_FOCUS_GAINED 133 
#define  SDL_WINDOWEVENT_FOCUS_LOST 132 
#define  SDL_WINDOWEVENT_MAXIMIZED 131 
#define  SDL_WINDOWEVENT_MINIMIZED 130 
#define  SDL_WINDOWEVENT_RESIZED 129 
#define  SDL_WINDOWEVENT_RESTORED 128 
 int /*<<< orphan*/  SDL_WasInit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SE_CHAR ; 
 int /*<<< orphan*/  SE_KEY ; 
 int /*<<< orphan*/  SE_MOUSE ; 
 int /*<<< orphan*/  Sys_Milliseconds () ; 
 TYPE_11__ cls ; 
 int /*<<< orphan*/  in_eventTime ; 
 TYPE_10__* in_joystick ; 
 TYPE_9__* keys ; 
 int /*<<< orphan*/  mouseActive ; 
 int /*<<< orphan*/  qfalse ; 
 int /*<<< orphan*/  qtrue ; 
 int /*<<< orphan*/  vidRestartTime ; 

__attribute__((used)) static void IN_ProcessEvents( void )
{
	SDL_Event e;
	keyNum_t key = 0;
	static keyNum_t lastKeyDown = 0;

	if( !SDL_WasInit( SDL_INIT_VIDEO ) )
			return;

	while( SDL_PollEvent( &e ) )
	{
		switch( e.type )
		{
			case SDL_KEYDOWN:
				if ( e.key.repeat && Key_GetCatcher( ) == 0 )
					break;

				if( ( key = IN_TranslateSDLToQ3Key( &e.key.keysym, qtrue ) ) )
					Com_QueueEvent( in_eventTime, SE_KEY, key, qtrue, 0, NULL );

				if( key == K_BACKSPACE )
					Com_QueueEvent( in_eventTime, SE_CHAR, CTRL('h'), 0, 0, NULL );
				else if( keys[K_CTRL].down && key >= 'a' && key <= 'z' )
					Com_QueueEvent( in_eventTime, SE_CHAR, CTRL(key), 0, 0, NULL );

				lastKeyDown = key;
				break;

			case SDL_KEYUP:
				if( ( key = IN_TranslateSDLToQ3Key( &e.key.keysym, qfalse ) ) )
					Com_QueueEvent( in_eventTime, SE_KEY, key, qfalse, 0, NULL );

				lastKeyDown = 0;
				break;

			case SDL_TEXTINPUT:
				if( lastKeyDown != K_CONSOLE )
				{
					char *c = e.text.text;

					// Quick and dirty UTF-8 to UTF-32 conversion
					while( *c )
					{
						int utf32 = 0;

						if( ( *c & 0x80 ) == 0 )
							utf32 = *c++;
						else if( ( *c & 0xE0 ) == 0xC0 ) // 110x xxxx
						{
							utf32 |= ( *c++ & 0x1F ) << 6;
							utf32 |= ( *c++ & 0x3F );
						}
						else if( ( *c & 0xF0 ) == 0xE0 ) // 1110 xxxx
						{
							utf32 |= ( *c++ & 0x0F ) << 12;
							utf32 |= ( *c++ & 0x3F ) << 6;
							utf32 |= ( *c++ & 0x3F );
						}
						else if( ( *c & 0xF8 ) == 0xF0 ) // 1111 0xxx
						{
							utf32 |= ( *c++ & 0x07 ) << 18;
							utf32 |= ( *c++ & 0x3F ) << 12;
							utf32 |= ( *c++ & 0x3F ) << 6;
							utf32 |= ( *c++ & 0x3F );
						}
						else
						{
							Com_DPrintf( "Unrecognised UTF-8 lead byte: 0x%x\n", (unsigned int)*c );
							c++;
						}

						if( utf32 != 0 )
						{
							if( IN_IsConsoleKey( 0, utf32 ) )
							{
								Com_QueueEvent( in_eventTime, SE_KEY, K_CONSOLE, qtrue, 0, NULL );
								Com_QueueEvent( in_eventTime, SE_KEY, K_CONSOLE, qfalse, 0, NULL );
							}
							else
								Com_QueueEvent( in_eventTime, SE_CHAR, utf32, 0, 0, NULL );
						}
          }
        }
				break;

			case SDL_MOUSEMOTION:
				if( mouseActive )
				{
					if( !e.motion.xrel && !e.motion.yrel )
						break;
					Com_QueueEvent( in_eventTime, SE_MOUSE, e.motion.xrel, e.motion.yrel, 0, NULL );
				}
				break;

			case SDL_MOUSEBUTTONDOWN:
			case SDL_MOUSEBUTTONUP:
				{
					int b;
					switch( e.button.button )
					{
						case SDL_BUTTON_LEFT:   b = K_MOUSE1;     break;
						case SDL_BUTTON_MIDDLE: b = K_MOUSE3;     break;
						case SDL_BUTTON_RIGHT:  b = K_MOUSE2;     break;
						case SDL_BUTTON_X1:     b = K_MOUSE4;     break;
						case SDL_BUTTON_X2:     b = K_MOUSE5;     break;
						default:                b = K_AUX1 + ( e.button.button - SDL_BUTTON_X2 + 1 ) % 16; break;
					}
					Com_QueueEvent( in_eventTime, SE_KEY, b,
						( e.type == SDL_MOUSEBUTTONDOWN ? qtrue : qfalse ), 0, NULL );
				}
				break;

			case SDL_MOUSEWHEEL:
				if( e.wheel.y > 0 )
				{
					Com_QueueEvent( in_eventTime, SE_KEY, K_MWHEELUP, qtrue, 0, NULL );
					Com_QueueEvent( in_eventTime, SE_KEY, K_MWHEELUP, qfalse, 0, NULL );
				}
				else if( e.wheel.y < 0 )
				{
					Com_QueueEvent( in_eventTime, SE_KEY, K_MWHEELDOWN, qtrue, 0, NULL );
					Com_QueueEvent( in_eventTime, SE_KEY, K_MWHEELDOWN, qfalse, 0, NULL );
				}
				break;

			case SDL_CONTROLLERDEVICEADDED:
			case SDL_CONTROLLERDEVICEREMOVED:
				if (in_joystick->integer)
					IN_InitJoystick();
				break;

			case SDL_QUIT:
				Cbuf_ExecuteText(EXEC_NOW, "quit Closed window\n");
				break;

			case SDL_WINDOWEVENT:
				switch( e.window.event )
				{
					case SDL_WINDOWEVENT_RESIZED:
						{
							int width, height;

							width = e.window.data1;
							height = e.window.data2;

							// ignore this event on fullscreen
							if( cls.glconfig.isFullscreen )
							{
								break;
							}

							// check if size actually changed
							if( cls.glconfig.vidWidth == width && cls.glconfig.vidHeight == height )
							{
								break;
							}

							Cvar_SetValue( "r_customwidth", width );
							Cvar_SetValue( "r_customheight", height );
							Cvar_Set( "r_mode", "-1" );

							// Wait until user stops dragging for 1 second, so
							// we aren't constantly recreating the GL context while
							// he tries to drag...
							vidRestartTime = Sys_Milliseconds( ) + 1000;
						}
						break;

					case SDL_WINDOWEVENT_MINIMIZED:    Cvar_SetValue( "com_minimized", 1 ); break;
					case SDL_WINDOWEVENT_RESTORED:
					case SDL_WINDOWEVENT_MAXIMIZED:    Cvar_SetValue( "com_minimized", 0 ); break;
					case SDL_WINDOWEVENT_FOCUS_LOST:   Cvar_SetValue( "com_unfocused", 1 ); break;
					case SDL_WINDOWEVENT_FOCUS_GAINED: Cvar_SetValue( "com_unfocused", 0 ); break;
				}
				break;

			default:
				break;
		}
	}
}