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
struct TYPE_3__ {char* name; int value; int /*<<< orphan*/ * segment; struct TYPE_3__* next; } ;
typedef  TYPE_1__ symbol_t ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int BSSSEG ; 
 int CODESEG ; 
 int MAX_OS_PATH ; 
 int /*<<< orphan*/ * SafeOpenWrite (char*) ; 
 int /*<<< orphan*/  StripExtension (char*) ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ *,char*,int,int,char*) ; 
 int /*<<< orphan*/  outputFilename ; 
 int /*<<< orphan*/  report (char*,char*) ; 
 int /*<<< orphan*/ * segment ; 
 int /*<<< orphan*/  strcat (char*,char*) ; 
 int /*<<< orphan*/  strcpy (char*,int /*<<< orphan*/ ) ; 
 TYPE_1__* symbols ; 

__attribute__((used)) static void WriteMapFile( void ) {
	FILE		*f;
	symbol_t	*s;
	char		imageName[MAX_OS_PATH];
	int			seg;

	strcpy( imageName, outputFilename );
	StripExtension( imageName );
	strcat( imageName, ".map" );

	report( "Writing %s...\n", imageName );

	f = SafeOpenWrite( imageName );
	for ( seg = CODESEG ; seg <= BSSSEG ; seg++ ) {
		for ( s = symbols ; s ; s = s->next ) {
			if ( s->name[0] == '$' ) {
				continue;	// skip locals
			}
			if ( &segment[seg] != s->segment ) {
				continue;
			}
			fprintf( f, "%i %8x %s\n", seg, s->value, s->name );
		}
	}
	fclose( f );
}