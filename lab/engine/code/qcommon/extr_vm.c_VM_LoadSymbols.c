#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int instructionCount; int* instructionPointers; int numSymbols; TYPE_2__* symbols; int /*<<< orphan*/  name; } ;
typedef  TYPE_1__ vm_t ;
struct TYPE_7__ {int symValue; int /*<<< orphan*/  symName; struct TYPE_7__* next; } ;
typedef  TYPE_2__ vmSymbol_t ;
typedef  int /*<<< orphan*/  symbols ;
typedef  int /*<<< orphan*/  name ;
struct TYPE_8__ {int /*<<< orphan*/  integer; } ;

/* Variables and functions */
 char* COM_Parse (char**) ; 
 int /*<<< orphan*/  COM_StripExtension (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  Com_Printf (char*,...) ; 
 int /*<<< orphan*/  Com_sprintf (char*,int,char*,char*) ; 
 int /*<<< orphan*/  FS_FreeFile (void*) ; 
 int /*<<< orphan*/  FS_ReadFile (char*,void**) ; 
 TYPE_2__* Hunk_Alloc (int,int /*<<< orphan*/ ) ; 
 int MAX_QPATH ; 
 int ParseHex (char*) ; 
 int /*<<< orphan*/  Q_strncpyz (int /*<<< orphan*/ ,char*,int) ; 
 TYPE_3__* com_developer ; 
 int /*<<< orphan*/  h_high ; 
 int strlen (char*) ; 

void VM_LoadSymbols( vm_t *vm ) {
	union {
		char	*c;
		void	*v;
	} mapfile;
	char *text_p, *token;
	char	name[MAX_QPATH];
	char	symbols[MAX_QPATH];
	vmSymbol_t	**prev, *sym;
	int		count;
	int		value;
	int		chars;
	int		segment;
	int		numInstructions;

	// don't load symbols if not developer
	if ( !com_developer->integer ) {
		return;
	}

	COM_StripExtension(vm->name, name, sizeof(name));
	Com_sprintf( symbols, sizeof( symbols ), "vm/%s.map", name );
	FS_ReadFile( symbols, &mapfile.v );
	if ( !mapfile.c ) {
		Com_Printf( "Couldn't load symbol file: %s\n", symbols );
		return;
	}

	numInstructions = vm->instructionCount;

	// parse the symbols
	text_p = mapfile.c;
	prev = &vm->symbols;
	count = 0;

	while ( 1 ) {
		token = COM_Parse( &text_p );
		if ( !token[0] ) {
			break;
		}
		segment = ParseHex( token );
		if ( segment ) {
			COM_Parse( &text_p );
			COM_Parse( &text_p );
			continue;		// only load code segment values
		}

		token = COM_Parse( &text_p );
		if ( !token[0] ) {
			Com_Printf( "WARNING: incomplete line at end of file\n" );
			break;
		}
		value = ParseHex( token );

		token = COM_Parse( &text_p );
		if ( !token[0] ) {
			Com_Printf( "WARNING: incomplete line at end of file\n" );
			break;
		}
		chars = strlen( token );
		sym = Hunk_Alloc( sizeof( *sym ) + chars, h_high );
		*prev = sym;
		prev = &sym->next;
		sym->next = NULL;

		// convert value from an instruction number to a code offset
		if ( value >= 0 && value < numInstructions ) {
			value = vm->instructionPointers[value];
		}

		sym->symValue = value;
		Q_strncpyz( sym->symName, token, chars + 1 );

		count++;
	}

	vm->numSymbols = count;
	Com_Printf( "%i symbols parsed from %s\n", count, symbols );
	FS_FreeFile( mapfile.v );
}