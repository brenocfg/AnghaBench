#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  qboolean ;
struct TYPE_8__ {long cursize; int readcount; int bit; int* data; int /*<<< orphan*/  oob; } ;
typedef  TYPE_2__ msg_t ;
struct TYPE_7__ {int outgoingSequence; } ;
struct TYPE_9__ {int challenge; TYPE_1__ netchan; } ;
typedef  TYPE_3__ client_t ;
typedef  int byte ;

/* Variables and functions */
 int /*<<< orphan*/  MSG_ReadLong (TYPE_2__*) ; 
 long SV_ENCODE_START ; 
 int /*<<< orphan*/  qfalse ; 

__attribute__((used)) static void SV_Netchan_Encode(client_t *client, msg_t *msg, const char *clientCommandString)
{
	long i, index;
	byte key, *string;
	int	srdc, sbit;
	qboolean soob;

	if ( msg->cursize < SV_ENCODE_START ) {
		return;
	}

	srdc = msg->readcount;
	sbit = msg->bit;
	soob = msg->oob;

	msg->bit = 0;
	msg->readcount = 0;
	msg->oob = qfalse;

	/* reliableAcknowledge = */ MSG_ReadLong(msg);

	msg->oob = soob;
	msg->bit = sbit;
	msg->readcount = srdc;

	string = (byte *) clientCommandString;
	index = 0;
	// xor the client challenge with the netchan sequence number
	key = client->challenge ^ client->netchan.outgoingSequence;
	for (i = SV_ENCODE_START; i < msg->cursize; i++) {
		// modify the key with the last received and with this message acknowledged client command
		if (!string[index])
			index = 0;
		if (string[index] > 127 || string[index] == '%') {
			key ^= '.' << (i & 1);
		}
		else {
			key ^= string[index] << (i & 1);
		}
		index++;
		// encode the data with this key
		*(msg->data + i) = *(msg->data + i) ^ key;
	}
}