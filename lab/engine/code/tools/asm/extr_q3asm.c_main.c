#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_3__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {struct TYPE_4__* next; } ;
typedef  TYPE_1__ symbol_t ;
struct TYPE_5__ {void* verbose; void* vanillaQ3Compatibility; void* writeMapFile; } ;

/* Variables and functions */
 int /*<<< orphan*/  Assemble () ; 
 int /*<<< orphan*/  Error (char*,...) ; 
 double I_FloatTime () ; 
 int /*<<< orphan*/  InitTables () ; 
 int /*<<< orphan*/  ParseOptionFile (char*) ; 
 int /*<<< orphan*/  ShowHelp (char*) ; 
 int /*<<< orphan*/ * asmFileNames ; 
 int /*<<< orphan*/  atoiNoCap (char*) ; 
 int /*<<< orphan*/  copystring (char*) ; 
 int errorCount ; 
 int /*<<< orphan*/  hashtable_stats (int /*<<< orphan*/ ) ; 
 size_t numAsmFiles ; 
 int /*<<< orphan*/  optable ; 
 TYPE_3__ options ; 
 int /*<<< orphan*/  outputFilename ; 
 void* qtrue ; 
 int /*<<< orphan*/  report (char*,double) ; 
 int /*<<< orphan*/  strcmp (char*,char*) ; 
 int /*<<< orphan*/  strcpy (int /*<<< orphan*/ ,char*) ; 
 TYPE_1__* symbols ; 
 int /*<<< orphan*/  symtable ; 
 int /*<<< orphan*/  symtablelen ; 

int main( int argc, char **argv ) {
	int			i;
	double		start, end;

//	_chdir( "/quake3/jccode/cgame/lccout" );	// hack for vc profiler

	if ( argc < 2 ) {
		ShowHelp( argv[0] );
	}

	start = I_FloatTime ();

	// default filename is "q3asm"
	strcpy( outputFilename, "q3asm" );
	numAsmFiles = 0;	

	for ( i = 1 ; i < argc ; i++ ) {
		if ( argv[i][0] != '-' ) {
			break;
		}
		if( !strcmp( argv[ i ], "-h" ) || 
		    !strcmp( argv[ i ], "--help" ) ||
		    !strcmp( argv[ i ], "-?") ) {
			ShowHelp( argv[0] );
		}

		if ( !strcmp( argv[i], "-o" ) ) {
			if ( i == argc - 1 ) {
				Error( "-o must precede a filename" );
			}
/* Timbo of Tremulous pointed out -o not working; stock ID q3asm folded in the change. Yay. */
			strcpy( outputFilename, argv[ i+1 ] );
			i++;
			continue;
		}

		if ( !strcmp( argv[i], "-f" ) ) {
			if ( i == argc - 1 ) {
				Error( "-f must precede a filename" );
			}
			ParseOptionFile( argv[ i+1 ] );
			i++;
			continue;
		}

		if (!strcmp(argv[i], "-b")) {
			if (i == argc - 1) {
				Error("-b requires an argument");
			}
			i++;
			symtablelen = atoiNoCap(argv[i]);
			continue;
		}

		if( !strcmp( argv[ i ], "-v" ) ) {
/* Verbosity option added by Timbo, 2002.09.14.
By default (no -v option), q3asm remains silent except for critical errors.
Verbosity turns on all messages, error or not.
Motivation: not wanting to scrollback for pages to find asm error.
*/
			options.verbose = qtrue;
			continue;
		}

		if( !strcmp( argv[ i ], "-m" ) ) {
			options.writeMapFile = qtrue;
			continue;
		}

		if( !strcmp( argv[ i ], "-vq3" ) ) {
			options.vanillaQ3Compatibility = qtrue;
			continue;
		}

		Error( "Unknown option: %s", argv[i] );
	}

	// the rest of the command line args are asm files
	for ( ; i < argc ; i++ ) {
		asmFileNames[ numAsmFiles ] = copystring( argv[ i ] );
		numAsmFiles++;
	}
	// In some case it Segfault without this check
	if ( numAsmFiles == 0 ) {
		Error( "No file to assemble" );
	}

	InitTables();
	Assemble();

	{
		symbol_t *s;

		for ( i = 0, s = symbols ; s ; s = s->next, i++ ) /* nop */ ;

		if (options.verbose)
		{
			report("%d symbols defined\n", i);
			hashtable_stats(symtable);
			hashtable_stats(optable);
		}
	}

	end = I_FloatTime ();
	report ("%5.0f seconds elapsed\n", end-start);

	return errorCount;
}