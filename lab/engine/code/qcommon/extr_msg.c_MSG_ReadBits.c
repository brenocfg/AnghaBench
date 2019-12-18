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
typedef  scalar_t__ qboolean ;
struct TYPE_6__ {int readcount; int cursize; int* data; int bit; scalar_t__ oob; } ;
typedef  TYPE_2__ msg_t ;
struct TYPE_5__ {int /*<<< orphan*/  tree; } ;
struct TYPE_7__ {TYPE_1__ decompressor; } ;

/* Variables and functions */
 int /*<<< orphan*/  Com_Error (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  CopyLittleLong (int*,int*) ; 
 int /*<<< orphan*/  CopyLittleShort (short*,int*) ; 
 int /*<<< orphan*/  ERR_DROP ; 
 int Huff_getBit (int*,int*) ; 
 int /*<<< orphan*/  Huff_offsetReceive (int /*<<< orphan*/ ,int*,int*,int*,int) ; 
 TYPE_3__ msgHuff ; 
 scalar_t__ qfalse ; 
 scalar_t__ qtrue ; 

int MSG_ReadBits( msg_t *msg, int bits ) {
	int			value;
	int			get;
	qboolean	sgn;
	int			i, nbits;
//	FILE*	fp;

	if ( msg->readcount > msg->cursize ) {
		return 0;
	}

	value = 0;

	if ( bits < 0 ) {
		bits = -bits;
		sgn = qtrue;
	} else {
		sgn = qfalse;
	}

	if (msg->oob) {
		if (msg->readcount + (bits>>3) > msg->cursize) {
			msg->readcount = msg->cursize + 1;
			return 0;
		}

		if(bits==8)
		{
			value = msg->data[msg->readcount];
			msg->readcount += 1;
			msg->bit += 8;
		}
		else if(bits==16)
		{
			short temp;
			
			CopyLittleShort(&temp, &msg->data[msg->readcount]);
			value = temp;
			msg->readcount += 2;
			msg->bit += 16;
		}
		else if(bits==32)
		{
			CopyLittleLong(&value, &msg->data[msg->readcount]);
			msg->readcount += 4;
			msg->bit += 32;
		}
		else
			Com_Error(ERR_DROP, "can't read %d bits", bits);
	} else {
		nbits = 0;
		if (bits&7) {
			nbits = bits&7;
			if (msg->bit + nbits > msg->cursize << 3) {
				msg->readcount = msg->cursize + 1;
				return 0;
			}
			for(i=0;i<nbits;i++) {
				value |= (Huff_getBit(msg->data, &msg->bit)<<i);
			}
			bits = bits - nbits;
		}
		if (bits) {
//			fp = fopen("c:\\netchan.bin", "a");
			for(i=0;i<bits;i+=8) {
				Huff_offsetReceive (msgHuff.decompressor.tree, &get, msg->data, &msg->bit, msg->cursize<<3);
//				fwrite(&get, 1, 1, fp);
				value = (unsigned int)value | ((unsigned int)get<<(i+nbits));

				if (msg->bit > msg->cursize<<3) {
					msg->readcount = msg->cursize + 1;
					return 0;
				}
			}
//			fclose(fp);
		}
		msg->readcount = (msg->bit>>3)+1;
	}
	if ( sgn && bits > 0 && bits < 32 ) {
		if ( value & ( 1 << ( bits - 1 ) ) ) {
			value |= -1 ^ ( ( 1 << bits ) - 1 );
		}
	}

	return value;
}