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
struct TYPE_5__ {float value; float time; int /*<<< orphan*/  shape; struct TYPE_5__* prev; struct TYPE_5__* next; } ;
typedef  TYPE_1__ lwKey ;
struct TYPE_6__ {int index; int type; int* name; int nkeys; void** behavior; TYPE_1__* key; } ;
typedef  TYPE_2__ lwEnvelope ;

/* Variables and functions */
 void* BEH_LINEAR ; 
 int /*<<< orphan*/  ID_LINE ; 
 int* _pico_alloc (int) ; 
 void* _pico_calloc (int,int) ; 
 int /*<<< orphan*/  lwListAdd (void**,TYPE_2__*) ; 
 int /*<<< orphan*/  strcpy (int*,char*) ; 

__attribute__((used)) static int add_tvel( float pos[], float vel[], lwEnvelope **elist, int *nenvs ){
	lwEnvelope *env;
	lwKey *key0, *key1;
	int i;

	for ( i = 0; i < 3; i++ ) {
		env = _pico_calloc( 1, sizeof( lwEnvelope ) );
		key0 = _pico_calloc( 1, sizeof( lwKey ) );
		key1 = _pico_calloc( 1, sizeof( lwKey ) );
		if ( !env || !key0 || !key1 ) {
			return 0;
		}

		key0->next = key1;
		key0->value = pos[ i ];
		key0->time = 0.0f;
		key1->prev = key0;
		key1->value = pos[ i ] + vel[ i ] * 30.0f;
		key1->time = 1.0f;
		key0->shape = key1->shape = ID_LINE;

		env->index = *nenvs + i + 1;
		env->type = 0x0301 + i;
		env->name = _pico_alloc( 11 );
		if ( env->name ) {
			strcpy( env->name, "Position.X" );
			env->name[ 9 ] += i;
		}
		env->key = key0;
		env->nkeys = 2;
		env->behavior[ 0 ] = BEH_LINEAR;
		env->behavior[ 1 ] = BEH_LINEAR;

		lwListAdd( (void **) elist, env );
	}

	*nenvs += 3;
	return env->index - 2;
}