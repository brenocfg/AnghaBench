#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {scalar_t__ compat; } ;
typedef  TYPE_1__ netchan_t ;
struct TYPE_10__ {int /*<<< orphan*/  data; int /*<<< orphan*/  cursize; } ;
typedef  TYPE_2__ msg_t ;

/* Variables and functions */
 int /*<<< orphan*/  CL_Netchan_Encode (TYPE_2__*) ; 
 scalar_t__ CL_Netchan_TransmitNextFragment (TYPE_1__*) ; 
 int /*<<< orphan*/  Com_DPrintf (char*) ; 
 int /*<<< orphan*/  MSG_WriteByte (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Netchan_Transmit (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clc_EOF ; 

void CL_Netchan_Transmit( netchan_t *chan, msg_t* msg ) {
	MSG_WriteByte( msg, clc_EOF );

#ifdef LEGACY_PROTOCOL
	if(chan->compat)
		CL_Netchan_Encode(msg);
#endif

	Netchan_Transmit(chan, msg->cursize, msg->data);
	
	// Transmit all fragments without delay
	while(CL_Netchan_TransmitNextFragment(chan))
	{
		Com_DPrintf("WARNING: #462 unsent fragments (not supposed to happen!)\n");
	}
}