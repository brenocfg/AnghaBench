#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  send_buf ;
struct TYPE_10__ {int outgoingSequence; size_t sock; scalar_t__ unsentFragmentStart; scalar_t__ unsentLength; int unsentBuffer; int /*<<< orphan*/  unsentFragments; int /*<<< orphan*/  lastSentSize; int /*<<< orphan*/  lastSentTime; int /*<<< orphan*/  remoteAddress; int /*<<< orphan*/  challenge; int /*<<< orphan*/  compat; } ;
typedef  TYPE_1__ netchan_t ;
struct TYPE_11__ {int /*<<< orphan*/  cursize; int /*<<< orphan*/  data; } ;
typedef  TYPE_2__ msg_t ;
typedef  int /*<<< orphan*/  byte ;
struct TYPE_13__ {int integer; } ;
struct TYPE_12__ {scalar_t__ integer; } ;

/* Variables and functions */
 int /*<<< orphan*/  Com_Printf (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int) ; 
 int FRAGMENT_BIT ; 
 int FRAGMENT_SIZE ; 
 int MAX_PACKETLEN ; 
 int /*<<< orphan*/  MSG_InitOOB (TYPE_2__*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  MSG_WriteData (TYPE_2__*,int,int) ; 
 int /*<<< orphan*/  MSG_WriteLong (TYPE_2__*,int) ; 
 int /*<<< orphan*/  MSG_WriteShort (TYPE_2__*,int) ; 
 int NETCHAN_GENCHECKSUM (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  NET_SendPacket (size_t,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 size_t NS_CLIENT ; 
 int /*<<< orphan*/  Sys_Milliseconds () ; 
 int /*<<< orphan*/ * netsrcString ; 
 int /*<<< orphan*/  qfalse ; 
 TYPE_4__* qport ; 
 TYPE_3__* showpackets ; 

void Netchan_TransmitNextFragment( netchan_t *chan ) {
	msg_t		send;
	byte		send_buf[MAX_PACKETLEN];
	int			fragmentLength;
	int			outgoingSequence;

	// write the packet header
	MSG_InitOOB (&send, send_buf, sizeof(send_buf));				// <-- only do the oob here

	outgoingSequence = chan->outgoingSequence | FRAGMENT_BIT;
	MSG_WriteLong(&send, outgoingSequence);

	// send the qport if we are a client
	if ( chan->sock == NS_CLIENT ) {
		MSG_WriteShort( &send, qport->integer );
	}

#ifdef LEGACY_PROTOCOL
	if(!chan->compat)
#endif
		MSG_WriteLong(&send, NETCHAN_GENCHECKSUM(chan->challenge, chan->outgoingSequence));

	// copy the reliable message to the packet first
	fragmentLength = FRAGMENT_SIZE;
	if ( chan->unsentFragmentStart  + fragmentLength > chan->unsentLength ) {
		fragmentLength = chan->unsentLength - chan->unsentFragmentStart;
	}

	MSG_WriteShort( &send, chan->unsentFragmentStart );
	MSG_WriteShort( &send, fragmentLength );
	MSG_WriteData( &send, chan->unsentBuffer + chan->unsentFragmentStart, fragmentLength );

	// send the datagram
	NET_SendPacket(chan->sock, send.cursize, send.data, chan->remoteAddress);
	
	// Store send time and size of this packet for rate control
	chan->lastSentTime = Sys_Milliseconds();
	chan->lastSentSize = send.cursize;

	if ( showpackets->integer ) {
		Com_Printf ("%s send %4i : s=%i fragment=%i,%i\n"
			, netsrcString[ chan->sock ]
			, send.cursize
			, chan->outgoingSequence
			, chan->unsentFragmentStart, fragmentLength);
	}

	chan->unsentFragmentStart += fragmentLength;

	// this exit condition is a little tricky, because a packet
	// that is exactly the fragment length still needs to send
	// a second packet of zero length so that the other side
	// can tell there aren't more to follow
	if ( chan->unsentFragmentStart == chan->unsentLength && fragmentLength != FRAGMENT_SIZE ) {
		chan->outgoingSequence++;
		chan->unsentFragments = qfalse;
	}
}