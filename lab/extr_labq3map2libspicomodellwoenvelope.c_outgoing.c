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
struct TYPE_6__ {int shape; float value; float time; float* param; TYPE_1__* prev; int /*<<< orphan*/  bias; int /*<<< orphan*/  continuity; int /*<<< orphan*/  tension; } ;
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

__attribute__((used)) static float outgoing( lwKey *key0, lwKey *key1 ){
	float a, b, d, t, out;

	switch ( key0->shape )
	{
	case ID_TCB:
		a = ( 1.0f - key0->tension )
			* ( 1.0f + key0->continuity )
			* ( 1.0f + key0->bias );
		b = ( 1.0f - key0->tension )
			* ( 1.0f - key0->continuity )
			* ( 1.0f - key0->bias );
		d = key1->value - key0->value;

		if ( key0->prev ) {
			t = ( key1->time - key0->time ) / ( key1->time - key0->prev->time );
			out = t * ( a * ( key0->value - key0->prev->value ) + b * d );
		}
		else{
			out = b * d;
		}
		break;

	case ID_LINE:
		d = key1->value - key0->value;
		if ( key0->prev ) {
			t = ( key1->time - key0->time ) / ( key1->time - key0->prev->time );
			out = t * ( key0->value - key0->prev->value + d );
		}
		else{
			out = d;
		}
		break;

	case ID_BEZI:
	case ID_HERM:
		out = key0->param[ 1 ];
		if ( key0->prev ) {
			out *= ( key1->time - key0->time ) / ( key1->time - key0->prev->time );
		}
		break;

	case ID_BEZ2:
		out = key0->param[ 3 ] * ( key1->time - key0->time );
		if ( fabs( key0->param[ 2 ] ) > 1e-5f ) {
			out /= key0->param[ 2 ];
		}
		else{
			out *= 1e5f;
		}
		break;

	case ID_STEP:
	default:
		out = 0.0f;
		break;
	}

	return out;
}