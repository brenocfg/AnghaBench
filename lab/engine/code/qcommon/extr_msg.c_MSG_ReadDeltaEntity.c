#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_5__ ;
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
struct TYPE_13__ {int offset; int bits; int /*<<< orphan*/  name; } ;
typedef  TYPE_1__ netField_t ;
struct TYPE_14__ {scalar_t__ bit; int readcount; } ;
typedef  TYPE_2__ msg_t ;
struct TYPE_15__ {int number; } ;
typedef  TYPE_3__ entityState_t ;
typedef  int /*<<< orphan*/  byte ;
struct TYPE_16__ {int integer; } ;

/* Variables and functions */
 int ARRAY_LEN (TYPE_1__*) ; 
 int /*<<< orphan*/  Com_Error (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  Com_Memset (TYPE_3__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  Com_Printf (char*,int,...) ; 
 int /*<<< orphan*/  ERR_DROP ; 
 scalar_t__ FLOAT_INT_BIAS ; 
 int FLOAT_INT_BITS ; 
 int GENTITYNUM_BITS ; 
 int MAX_GENTITIES ; 
 int MSG_ReadBits (TYPE_2__*,int) ; 
 int MSG_ReadByte (TYPE_2__*) ; 
 TYPE_5__* cl_shownet ; 
 TYPE_1__* entityStateFields ; 

void MSG_ReadDeltaEntity( msg_t *msg, entityState_t *from, entityState_t *to, 
						 int number) {
	int			i, lc;
	int			numFields;
	netField_t	*field;
	int			*fromF, *toF;
	int			print;
	int			trunc;
	int			startBit, endBit;

	if ( number < 0 || number >= MAX_GENTITIES) {
		Com_Error( ERR_DROP, "Bad delta entity number: %i", number );
	}

	if ( msg->bit == 0 ) {
		startBit = msg->readcount * 8 - GENTITYNUM_BITS;
	} else {
		startBit = ( msg->readcount - 1 ) * 8 + msg->bit - GENTITYNUM_BITS;
	}

	// check for a remove
	if ( MSG_ReadBits( msg, 1 ) == 1 ) {
		Com_Memset( to, 0, sizeof( *to ) );	
		to->number = MAX_GENTITIES - 1;
		if ( cl_shownet && ( cl_shownet->integer >= 2 || cl_shownet->integer == -1 ) ) {
			Com_Printf( "%3i: #%-3i remove\n", msg->readcount, number );
		}
		return;
	}

	// check for no delta
	if ( MSG_ReadBits( msg, 1 ) == 0 ) {
		*to = *from;
		to->number = number;
		return;
	}

	numFields = ARRAY_LEN( entityStateFields );
	lc = MSG_ReadByte(msg);

	if ( lc > numFields || lc < 0 ) {
		Com_Error( ERR_DROP, "invalid entityState field count" );
	}

	// shownet 2/3 will interleave with other printed info, -1 will
	// just print the delta records`
	if ( cl_shownet && ( cl_shownet->integer >= 2 || cl_shownet->integer == -1 ) ) {
		print = 1;
		Com_Printf( "%3i: #%-3i ", msg->readcount, to->number );
	} else {
		print = 0;
	}

	to->number = number;

	for ( i = 0, field = entityStateFields ; i < lc ; i++, field++ ) {
		fromF = (int *)( (byte *)from + field->offset );
		toF = (int *)( (byte *)to + field->offset );

		if ( ! MSG_ReadBits( msg, 1 ) ) {
			// no change
			*toF = *fromF;
		} else {
			if ( field->bits == 0 ) {
				// float
				if ( MSG_ReadBits( msg, 1 ) == 0 ) {
						*(float *)toF = 0.0f; 
				} else {
					if ( MSG_ReadBits( msg, 1 ) == 0 ) {
						// integral float
						trunc = MSG_ReadBits( msg, FLOAT_INT_BITS );
						// bias to allow equal parts positive and negative
						trunc -= FLOAT_INT_BIAS;
						*(float *)toF = trunc; 
						if ( print ) {
							Com_Printf( "%s:%i ", field->name, trunc );
						}
					} else {
						// full floating point value
						*toF = MSG_ReadBits( msg, 32 );
						if ( print ) {
							Com_Printf( "%s:%f ", field->name, *(float *)toF );
						}
					}
				}
			} else {
				if ( MSG_ReadBits( msg, 1 ) == 0 ) {
					*toF = 0;
				} else {
					// integer
					*toF = MSG_ReadBits( msg, field->bits );
					if ( print ) {
						Com_Printf( "%s:%i ", field->name, *toF );
					}
				}
			}
//			pcount[i]++;
		}
	}
	for ( i = lc, field = &entityStateFields[lc] ; i < numFields ; i++, field++ ) {
		fromF = (int *)( (byte *)from + field->offset );
		toF = (int *)( (byte *)to + field->offset );
		// no change
		*toF = *fromF;
	}

	if ( print ) {
		if ( msg->bit == 0 ) {
			endBit = msg->readcount * 8 - GENTITYNUM_BITS;
		} else {
			endBit = ( msg->readcount - 1 ) * 8 + msg->bit - GENTITYNUM_BITS;
		}
		Com_Printf( " (%i bits)\n", endBit - startBit  );
	}
}