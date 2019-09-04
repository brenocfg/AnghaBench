#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ writeMapFile; } ;
struct TYPE_3__ {int segmentBase; int imageUsed; } ;

/* Variables and functions */
 int /*<<< orphan*/  AssembleLine () ; 
 size_t BSSSEG ; 
 size_t DATASEG ; 
 int /*<<< orphan*/  DefaultExtension (char*,char*) ; 
 int /*<<< orphan*/  DefineSymbol (char*,int) ; 
 char* ExtractLine (char*) ; 
 size_t JTRGSEG ; 
 size_t LITSEG ; 
 int /*<<< orphan*/  LoadFile (char*,void**) ; 
 int MAX_OS_PATH ; 
 int NUM_SEGMENTS ; 
 int /*<<< orphan*/  WriteMapFile () ; 
 int /*<<< orphan*/  WriteVmFile () ; 
 int /*<<< orphan*/ * asmFileNames ; 
 char** asmFiles ; 
 int currentFileIndex ; 
 scalar_t__ currentFileLine ; 
 int /*<<< orphan*/  currentFileName ; 
 int /*<<< orphan*/  fflush (int /*<<< orphan*/ *) ; 
 scalar_t__ instructionCount ; 
 int numAsmFiles ; 
 TYPE_2__ options ; 
 int /*<<< orphan*/  outputFilename ; 
 int passNumber ; 
 int /*<<< orphan*/  report (char*,int,...) ; 
 TYPE_1__* segment ; 
 int /*<<< orphan*/  sort_symbols () ; 
 scalar_t__ stackSize ; 
 int /*<<< orphan*/  strcpy (char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void Assemble( void ) {
	int		i;
	char	filename[MAX_OS_PATH];
	char		*ptr;

	report( "outputFilename: %s\n", outputFilename );

	for ( i = 0 ; i < numAsmFiles ; i++ ) {
		strcpy( filename, asmFileNames[ i ] );
		DefaultExtension( filename, ".asm" );
		LoadFile( filename, (void **)&asmFiles[i] );
	}

	// assemble
	for ( passNumber = 0 ; passNumber < 2 ; passNumber++ ) {
		segment[LITSEG].segmentBase = segment[DATASEG].imageUsed;
		segment[BSSSEG].segmentBase = segment[LITSEG].segmentBase + segment[LITSEG].imageUsed;
		segment[JTRGSEG].segmentBase = segment[BSSSEG].segmentBase + segment[BSSSEG].imageUsed;
		for ( i = 0 ; i < NUM_SEGMENTS ; i++ ) {
			segment[i].imageUsed = 0;
		}
		segment[DATASEG].imageUsed = 4;		// skip the 0 byte, so NULL pointers are fixed up properly
		instructionCount = 0;

		for ( i = 0 ; i < numAsmFiles ; i++ ) {
			currentFileIndex = i;
			currentFileName = asmFileNames[ i ];
			currentFileLine = 0;
			report("pass %i: %s\n", passNumber, currentFileName );
			fflush( NULL );
			ptr = asmFiles[i];
			while ( ptr ) {
				ptr = ExtractLine( ptr );
				AssembleLine();
			}
		}

		// align all segment
		for ( i = 0 ; i < NUM_SEGMENTS ; i++ ) {
			segment[i].imageUsed = (segment[i].imageUsed + 3) & ~3;
		}
		if (passNumber == 0) {
			sort_symbols();
		}
	}

	// reserve the stack in bss
	DefineSymbol( "_stackStart", segment[BSSSEG].imageUsed );
	segment[BSSSEG].imageUsed += stackSize;
	DefineSymbol( "_stackEnd", segment[BSSSEG].imageUsed );

	// write the image
	WriteVmFile();

	// write the map file even if there were errors
	if( options.writeMapFile ) {
		WriteMapFile();
	}
}