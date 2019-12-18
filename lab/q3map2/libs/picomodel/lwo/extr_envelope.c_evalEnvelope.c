#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {float value; float time; int shape; struct TYPE_10__* next; struct TYPE_10__* prev; } ;
typedef  TYPE_1__ lwKey ;
struct TYPE_11__ {int nkeys; int* behavior; TYPE_1__* key; } ;
typedef  TYPE_2__ lwEnvelope ;

/* Variables and functions */
#define  BEH_CONSTANT 139 
#define  BEH_LINEAR 138 
#define  BEH_OFFSET 137 
#define  BEH_OSCILLATE 136 
#define  BEH_REPEAT 135 
#define  BEH_RESET 134 
#define  ID_BEZ2 133 
#define  ID_BEZI 132 
#define  ID_HERM 131 
#define  ID_LINE 130 
#define  ID_STEP 129 
#define  ID_TCB 128 
 int /*<<< orphan*/  bez2 (TYPE_1__*,TYPE_1__*,float) ; 
 int /*<<< orphan*/  hermite (float,float*,float*,float*,float*) ; 
 float incoming (TYPE_1__*,TYPE_1__*) ; 
 float outgoing (TYPE_1__*,TYPE_1__*) ; 
 float range (float,float,float,int*) ; 

float evalEnvelope( lwEnvelope *env, float time ){
	lwKey *key0, *key1, *skey, *ekey;
	float t, h1, h2, h3, h4, in, out, offset = 0.0f;
	int noff;


	/* if there's no key, the value is 0 */

	if ( env->nkeys == 0 ) {
		return 0.0f;
	}

	/* if there's only one key, the value is constant */

	if ( env->nkeys == 1 ) {
		return env->key->value;
	}

	/* find the first and last keys */

	skey = ekey = env->key;
	while ( ekey->next ) ekey = ekey->next;

	/* use pre-behavior if time is before first key time */

	if ( time < skey->time ) {
		switch ( env->behavior[ 0 ] )
		{
		case BEH_RESET:
			return 0.0f;

		case BEH_CONSTANT:
			return skey->value;

		case BEH_REPEAT:
			time = range( time, skey->time, ekey->time, NULL );
			break;

		case BEH_OSCILLATE:
			time = range( time, skey->time, ekey->time, &noff );
			if ( noff % 2 ) {
				time = ekey->time - skey->time - time;
			}
			break;

		case BEH_OFFSET:
			time = range( time, skey->time, ekey->time, &noff );
			offset = noff * ( ekey->value - skey->value );
			break;

		case BEH_LINEAR:
			out = outgoing( skey, skey->next )
				  / ( skey->next->time - skey->time );
			return out * ( time - skey->time ) + skey->value;
		}
	}

	/* use post-behavior if time is after last key time */

	else if ( time > ekey->time ) {
		switch ( env->behavior[ 1 ] )
		{
		case BEH_RESET:
			return 0.0f;

		case BEH_CONSTANT:
			return ekey->value;

		case BEH_REPEAT:
			time = range( time, skey->time, ekey->time, NULL );
			break;

		case BEH_OSCILLATE:
			time = range( time, skey->time, ekey->time, &noff );
			if ( noff % 2 ) {
				time = ekey->time - skey->time - time;
			}
			break;

		case BEH_OFFSET:
			time = range( time, skey->time, ekey->time, &noff );
			offset = noff * ( ekey->value - skey->value );
			break;

		case BEH_LINEAR:
			in = incoming( ekey->prev, ekey )
				 / ( ekey->time - ekey->prev->time );
			return in * ( time - ekey->time ) + ekey->value;
		}
	}

	/* get the endpoints of the interval being evaluated */

	key0 = env->key;
	while ( time > key0->next->time )
		key0 = key0->next;
	key1 = key0->next;

	/* check for singularities first */

	if ( time == key0->time ) {
		return key0->value + offset;
	}
	else if ( time == key1->time ) {
		return key1->value + offset;
	}

	/* get interval length, time in [0, 1] */

	t = ( time - key0->time ) / ( key1->time - key0->time );

	/* interpolate */

	switch ( key1->shape )
	{
	case ID_TCB:
	case ID_BEZI:
	case ID_HERM:
		out = outgoing( key0, key1 );
		in = incoming( key0, key1 );
		hermite( t, &h1, &h2, &h3, &h4 );
		return h1 * key0->value + h2 * key1->value + h3 * out + h4 * in + offset;

	case ID_BEZ2:
		return bez2( key0, key1, time ) + offset;

	case ID_LINE:
		return key0->value + t * ( key1->value - key0->value ) + offset;

	case ID_STEP:
		return key0->value + offset;

	default:
		return offset;
	}
}