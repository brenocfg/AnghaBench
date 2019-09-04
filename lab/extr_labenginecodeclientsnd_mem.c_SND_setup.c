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
typedef  int /*<<< orphan*/  sndBuffer ;
struct TYPE_3__ {int integer; } ;
typedef  TYPE_1__ cvar_t ;

/* Variables and functions */
 int CVAR_ARCHIVE ; 
 int CVAR_LATCH ; 
 int /*<<< orphan*/  Com_Printf (char*) ; 
 TYPE_1__* Cvar_Get (char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  DEF_COMSOUNDMEGS ; 
 int SND_CHUNK_SIZE ; 
 int /*<<< orphan*/ * buffer ; 
 int /*<<< orphan*/ * freelist ; 
 int inUse ; 
 void* malloc (int) ; 
 void* sfxScratchBuffer ; 
 int /*<<< orphan*/ * sfxScratchPointer ; 

void SND_setup(void) {
	sndBuffer *p, *q;
	cvar_t	*cv;
	int scs;

	cv = Cvar_Get( "com_soundMegs", DEF_COMSOUNDMEGS, CVAR_LATCH | CVAR_ARCHIVE );

	scs = (cv->integer*1536);

	buffer = malloc(scs*sizeof(sndBuffer) );
	// allocate the stack based hunk allocator
	sfxScratchBuffer = malloc(SND_CHUNK_SIZE * sizeof(short) * 4);	//Hunk_Alloc(SND_CHUNK_SIZE * sizeof(short) * 4);
	sfxScratchPointer = NULL;

	inUse = scs*sizeof(sndBuffer);
	p = buffer;;
	q = p + scs;
	while (--q > p)
		*(sndBuffer **)q = q-1;
	
	*(sndBuffer **)q = NULL;
	freelist = p + scs - 1;

	Com_Printf("Sound memory manager started\n");
}