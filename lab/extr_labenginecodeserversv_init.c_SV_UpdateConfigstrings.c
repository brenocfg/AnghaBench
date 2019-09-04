#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {scalar_t__* csUpdated; TYPE_2__* gentity; } ;
typedef  TYPE_3__ client_t ;
struct TYPE_6__ {int svFlags; } ;
struct TYPE_7__ {TYPE_1__ r; } ;

/* Variables and functions */
 int CS_SERVERINFO ; 
 int MAX_CONFIGSTRINGS ; 
 int SVF_NOSERVERINFO ; 
 int /*<<< orphan*/  SV_SendConfigstring (TYPE_3__*,int) ; 
 scalar_t__ qfalse ; 

void SV_UpdateConfigstrings(client_t *client)
{
	int index;

	for( index = 0; index < MAX_CONFIGSTRINGS; index++ ) {
		// if the CS hasn't changed since we went to CS_PRIMED, ignore
		if(!client->csUpdated[index])
			continue;

		// do not always send server info to all clients
		if ( index == CS_SERVERINFO && client->gentity &&
			(client->gentity->r.svFlags & SVF_NOSERVERINFO) ) {
			continue;
		}
		SV_SendConfigstring(client, index);
		client->csUpdated[index] = qfalse;
	}
}