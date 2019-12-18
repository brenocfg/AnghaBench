#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ fileHandle_t ;
typedef  int /*<<< orphan*/  buffer ;
struct TYPE_6__ {scalar_t__ integer; } ;
struct TYPE_5__ {char* string; } ;
struct TYPE_4__ {int timeDemoStart; double timeDemoFrames; char** timeDemoDurations; int /*<<< orphan*/  timeDemoMaxDuration; int /*<<< orphan*/  timeDemoMinDuration; } ;

/* Variables and functions */
 int /*<<< orphan*/  CL_DemoFrameDurationSDev () ; 
 int /*<<< orphan*/  CL_Disconnect (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CL_NextDemo () ; 
 int /*<<< orphan*/  Com_Printf (char*,char*) ; 
 int /*<<< orphan*/  Com_sprintf (char*,int,char*,double,int,double,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FS_FCloseFile (scalar_t__) ; 
 scalar_t__ FS_FOpenFileWrite (char*) ; 
 int /*<<< orphan*/  FS_Printf (scalar_t__,char*,char*) ; 
 int MAX_STRING_CHARS ; 
 int MAX_TIMEDEMO_DURATIONS ; 
 int Sys_Milliseconds () ; 
 TYPE_3__* cl_timedemo ; 
 TYPE_2__* cl_timedemoLog ; 
 TYPE_1__ clc ; 
 int /*<<< orphan*/  qtrue ; 
 scalar_t__ strlen (char*) ; 

void CL_DemoCompleted( void )
{
	char buffer[ MAX_STRING_CHARS ];

	if( cl_timedemo && cl_timedemo->integer )
	{
		int	time;
		
		time = Sys_Milliseconds() - clc.timeDemoStart;
		if( time > 0 )
		{
			// Millisecond times are frame durations:
			// minimum/average/maximum/std deviation
			Com_sprintf( buffer, sizeof( buffer ),
					"%i frames %3.1f seconds %3.1f fps %d.0/%.1f/%d.0/%.1f ms\n",
					clc.timeDemoFrames,
					time/1000.0,
					clc.timeDemoFrames*1000.0 / time,
					clc.timeDemoMinDuration,
					time / (float)clc.timeDemoFrames,
					clc.timeDemoMaxDuration,
					CL_DemoFrameDurationSDev( ) );
			Com_Printf( "%s", buffer );

			// Write a log of all the frame durations
			if( cl_timedemoLog && strlen( cl_timedemoLog->string ) > 0 )
			{
				int i;
				int numFrames;
				fileHandle_t f;

				if( ( clc.timeDemoFrames - 1 ) > MAX_TIMEDEMO_DURATIONS )
					numFrames = MAX_TIMEDEMO_DURATIONS;
				else
					numFrames = clc.timeDemoFrames - 1;

				f = FS_FOpenFileWrite( cl_timedemoLog->string );
				if( f )
				{
					FS_Printf( f, "# %s", buffer );

					for( i = 0; i < numFrames; i++ )
						FS_Printf( f, "%d\n", clc.timeDemoDurations[ i ] );

					FS_FCloseFile( f );
					Com_Printf( "%s written\n", cl_timedemoLog->string );
				}
				else
				{
					Com_Printf( "Couldn't open %s for writing\n",
							cl_timedemoLog->string );
				}
			}
		}
	}

	CL_Disconnect( qtrue );
	CL_NextDemo();
}