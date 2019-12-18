#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  qboolean ;
typedef  int /*<<< orphan*/  msg_t ;
struct TYPE_4__ {scalar_t__ compat; int /*<<< orphan*/  netchan; } ;
typedef  TYPE_1__ client_t ;

/* Variables and functions */
 int Netchan_Process (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SV_Netchan_Decode (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  qfalse ; 
 int /*<<< orphan*/  qtrue ; 

qboolean SV_Netchan_Process( client_t *client, msg_t *msg ) {
	int ret;
	ret = Netchan_Process( &client->netchan, msg );
	if (!ret)
		return qfalse;

#ifdef LEGACY_PROTOCOL
	if(client->compat)
		SV_Netchan_Decode(client, msg);
#endif

	return qtrue;
}