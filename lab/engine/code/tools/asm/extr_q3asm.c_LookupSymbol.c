#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int hash; int value; TYPE_1__* segment; int /*<<< orphan*/  name; } ;
typedef  TYPE_2__ symbol_t ;
struct TYPE_7__ {scalar_t__ data; struct TYPE_7__* next; } ;
typedef  TYPE_3__ hashchain_t ;
struct TYPE_5__ {int segmentBase; } ;

/* Variables and functions */
 int /*<<< orphan*/  CodeError (char*,char*) ; 
 int /*<<< orphan*/  DefineSymbol (char*,int /*<<< orphan*/ ) ; 
 int HashString (char*) ; 
 int MAX_LINE_LENGTH ; 
 int currentFileIndex ; 
 TYPE_3__* hashtable_get (int /*<<< orphan*/ ,int) ; 
 int passNumber ; 
 int /*<<< orphan*/  sprintf (char*,char*,char*,int) ; 
 int /*<<< orphan*/  strcmp (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  symtable ; 

__attribute__((used)) static int LookupSymbol( char *sym ) {
	symbol_t	*s;
	char		expanded[MAX_LINE_LENGTH];
	int			hash;
	hashchain_t *hc;

	if ( passNumber == 0 ) {
		return 0;
	}

	// add the file prefix to local symbols to guarantee unique
	if ( sym[0] == '$' ) {
		sprintf( expanded, "%s_%i", sym, currentFileIndex );
		sym = expanded;
	}

	hash = HashString( sym );

/*
  Hand optimization by PhaethonH

  Using a hash table with chain/bucket for lookups alone sped up q3asm by almost 3x for me.
 -PH
*/
	for (hc = hashtable_get(symtable, hash); hc; hc = hc->next) {
		s = (symbol_t*)hc->data;  /* ugly typecasting, but it's fast! */
		if ( (hash == s->hash) && !strcmp(sym, s->name) ) {
			return s->segment->segmentBase + s->value;
		}
	}

	CodeError( "error: symbol %s undefined\n", sym );
	passNumber = 0;
	DefineSymbol( sym, 0 );	// so more errors aren't printed
	passNumber = 1;
	return 0;
}