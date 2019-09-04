#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {void* value; void* key; struct TYPE_5__* next; } ;
typedef  TYPE_1__ epair_t ;
struct TYPE_6__ {TYPE_1__* epairs; } ;
typedef  TYPE_2__ entity_t ;

/* Variables and functions */
 int /*<<< orphan*/  EPAIR_STRCMP (void*,char const*) ; 
 void* copystring (char const*) ; 
 int /*<<< orphan*/  free (void*) ; 
 TYPE_1__* safe_malloc (int) ; 

void SetKeyValue( entity_t *ent, const char *key, const char *value ){
	epair_t *ep;


	/* check for existing epair */
	for ( ep = ent->epairs; ep != NULL; ep = ep->next )
	{
		if ( !EPAIR_STRCMP( ep->key, key ) ) {
			free( ep->value );
			ep->value = copystring( value );
			return;
		}
	}

	/* create new epair */
	ep = safe_malloc( sizeof( *ep ) );
	ep->next = ent->epairs;
	ent->epairs = ep;
	ep->key = copystring( key );
	ep->value = copystring( value );
}