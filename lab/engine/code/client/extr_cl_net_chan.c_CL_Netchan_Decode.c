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
struct TYPE_5__ {int readcount; int bit; int oob; int* data; long cursize; } ;
typedef  TYPE_1__ msg_t ;
typedef  int byte ;
struct TYPE_6__ {int challenge; scalar_t__* reliableCommands; } ;

/* Variables and functions */
 long CL_DECODE_START ; 
 int LittleLong (unsigned int) ; 
 int MAX_RELIABLE_COMMANDS ; 
 long MSG_ReadLong (TYPE_1__*) ; 
 TYPE_2__ clc ; 

__attribute__((used)) static void CL_Netchan_Decode( msg_t *msg ) {
	long reliableAcknowledge, i, index;
	byte key, *string;
        int	srdc, sbit, soob;

        srdc = msg->readcount;
        sbit = msg->bit;
        soob = msg->oob;
        
        msg->oob = 0;
        
	reliableAcknowledge = MSG_ReadLong(msg);

        msg->oob = soob;
        msg->bit = sbit;
        msg->readcount = srdc;

	string = (byte *) clc.reliableCommands[ reliableAcknowledge & (MAX_RELIABLE_COMMANDS-1) ];
	index = 0;
	// xor the client challenge with the netchan sequence number (need something that changes every message)
	key = clc.challenge ^ LittleLong( *(unsigned *)msg->data );
	for (i = msg->readcount + CL_DECODE_START; i < msg->cursize; i++) {
		// modify the key with the last sent and with this message acknowledged client command
		if (!string[index])
			index = 0;
		if (string[index] > 127 || string[index] == '%') {
			key ^= '.' << (i & 1);
		}
		else {
			key ^= string[index] << (i & 1);
		}
		index++;
		// decode the data with this key
		*(msg->data + i) = *(msg->data + i) ^ key;
	}
}