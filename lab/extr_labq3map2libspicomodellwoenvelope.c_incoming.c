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
struct TYPE_6__ {int shape; float value; float time; float* param; TYPE_1__* next; int /*<<< orphan*/  bias; int /*<<< orphan*/  continuity; int /*<<< orphan*/  tension; } ;
typedef  TYPE_2__ lwKey ;
struct TYPE_5__ {float time; float value; } ;

/* Variables and functions */
#define  ID_BEZ2 133 
#define  ID_BEZI 132 
#define  ID_HERM 131 
#define  ID_LINE 130 
#define  ID_STEP 129 
#define  ID_TCB 128 
 float fabs (float) ; 

__attribute__((used)) static float incoming( lwKey *key0, lwKey *key1 ){
	float a, b, d, t, in;

	switch ( key1->shape )
	{
	case ID_LINE:
		d = key1->value - key0->value;
		if ( key1->next ) {
			t = ( key1->time - key0->time ) / ( key1->next->time - key0->time );
			in = t * ( key1->next->value - key1->value + d );
		}
		else{
			in = d;
		}
		break;

	case ID_TCB:
		a = ( 1.0f - key1->tension )
			* ( 1.0f - key1->continuity )
			* ( 1.0f + key1->bias );
		b = ( 1.0f - key1->tension )
			* ( 1.0f + key1->continuity )
			* ( 1.0f - key1->bias );
		d = key1->value - key0->value;

		if ( key1->next ) {
			t = ( key1->time - key0->time ) / ( key1->next->time - key0->time );
			in = t * ( b * ( key1->next->value - key1->value ) + a * d );
		}
		else{
			in = a * d;
		}
		break;

	case ID_BEZI:
	case ID_HERM:
		in = key1->param[ 0 ];
		if ( key1->next ) {
			in *= ( key1->time - key0->time ) / ( key1->next->time - key0->time );
		}
		break;
		return in;

	case ID_BEZ2:
		in = key1->param[ 1 ] * ( key1->time - key0->time );
		if ( fabs( key1->param[ 0 ] ) > 1e-5f ) {
			in /= key1->param[ 0 ];
		}
		else{
			in *= 1e5f;
		}
		break;

	case ID_STEP:
	default:
		in = 0.0f;
		break;
	}

	return in;
}