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
struct TYPE_4__ {scalar_t__ compat; } ;
typedef  TYPE_1__ netchan_t ;
typedef  int /*<<< orphan*/  msg_t ;

/* Variables and functions */
 int /*<<< orphan*/  CL_Netchan_Decode (int /*<<< orphan*/ *) ; 
 int Netchan_Process (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  qfalse ; 
 int /*<<< orphan*/  qtrue ; 

qboolean CL_Netchan_Process( netchan_t *chan, msg_t *msg ) {
	int ret;

	ret = Netchan_Process( chan, msg );
	if (!ret)
		return qfalse;

#ifdef LEGACY_PROTOCOL
	if(chan->compat)
		CL_Netchan_Decode(msg);
#endif

	return qtrue;
}