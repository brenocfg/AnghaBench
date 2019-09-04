#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {char* key; char* value; struct TYPE_4__* next; } ;
typedef  TYPE_1__ epair_t ;
struct TYPE_5__ {TYPE_1__* epairs; } ;
typedef  TYPE_2__ entity_t ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  Q_stricmp (char*,char*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ *,char*,char*,char*) ; 

__attribute__((used)) static void ConvertEPairs( FILE *f, entity_t *e ){
	epair_t *ep;


	/* walk epairs */
	for ( ep = e->epairs; ep != NULL; ep = ep->next )
	{
		/* ignore empty keys/values */
		if ( ep->key[ 0 ] == '\0' || ep->value[ 0 ] == '\0' ) {
			continue;
		}

		/* ignore model keys with * prefixed values */
		if ( !Q_stricmp( ep->key, "model" ) && ep->value[ 0 ] == '*' ) {
			continue;
		}

		/* emit the epair */
		fprintf( f, "\t\"%s\" \"%s\"\n", ep->key, ep->value );
	}
}