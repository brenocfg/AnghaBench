#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  vinfo ;
typedef  int Uint16 ;
struct TYPE_9__ {int /*<<< orphan*/  deviceSupportsGamma; } ;
struct TYPE_8__ {scalar_t__ integer; } ;
struct TYPE_7__ {int /*<<< orphan*/  (* Printf ) (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ;} ;
struct TYPE_6__ {int dwOSVersionInfoSize; int dwMajorVersion; scalar_t__ dwPlatformId; } ;
typedef  TYPE_1__ OSVERSIONINFO ;

/* Variables and functions */
 int /*<<< orphan*/  GetVersionEx (TYPE_1__*) ; 
 int /*<<< orphan*/  PRINT_DEVELOPER ; 
 int /*<<< orphan*/  SDL_GetError () ; 
 scalar_t__ SDL_SetWindowGammaRamp (int /*<<< orphan*/ ,int*,int*,int*) ; 
 int /*<<< orphan*/  SDL_window ; 
 scalar_t__ VER_PLATFORM_WIN32_NT ; 
 TYPE_4__ glConfig ; 
 TYPE_3__* r_ignorehwgamma ; 
 TYPE_2__ ri ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 

void GLimp_SetGamma( unsigned char red[256], unsigned char green[256], unsigned char blue[256] )
{
	Uint16 table[3][256];
	int i, j;

	if( !glConfig.deviceSupportsGamma || r_ignorehwgamma->integer > 0 )
		return;

	for (i = 0; i < 256; i++)
	{
		table[0][i] = ( ( ( Uint16 ) red[i] ) << 8 ) | red[i];
		table[1][i] = ( ( ( Uint16 ) green[i] ) << 8 ) | green[i];
		table[2][i] = ( ( ( Uint16 ) blue[i] ) << 8 ) | blue[i];
	}

#ifdef _WIN32
#include <windows.h>

	// Win2K and newer put this odd restriction on gamma ramps...
	{
		OSVERSIONINFO	vinfo;

		vinfo.dwOSVersionInfoSize = sizeof( vinfo );
		GetVersionEx( &vinfo );
		if( vinfo.dwMajorVersion >= 5 && vinfo.dwPlatformId == VER_PLATFORM_WIN32_NT )
		{
			ri.Printf( PRINT_DEVELOPER, "performing gamma clamp.\n" );
			for( j = 0 ; j < 3 ; j++ )
			{
				for( i = 0 ; i < 128 ; i++ )
				{
					if( table[ j ] [ i] > ( ( 128 + i ) << 8 ) )
						table[ j ][ i ] = ( 128 + i ) << 8;
				}

				if( table[ j ] [127 ] > 254 << 8 )
					table[ j ][ 127 ] = 254 << 8;
			}
		}
	}
#endif

	// enforce constantly increasing
	for (j = 0; j < 3; j++)
	{
		for (i = 1; i < 256; i++)
		{
			if (table[j][i] < table[j][i-1])
				table[j][i] = table[j][i-1];
		}
	}

	if (SDL_SetWindowGammaRamp(SDL_window, table[0], table[1], table[2]) < 0)
	{
		ri.Printf( PRINT_DEVELOPER, "SDL_SetWindowGammaRamp() failed: %s\n", SDL_GetError() );
	}
}