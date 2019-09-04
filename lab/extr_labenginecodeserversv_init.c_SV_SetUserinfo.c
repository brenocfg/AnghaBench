#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int integer; } ;
struct TYPE_5__ {TYPE_1__* clients; } ;
struct TYPE_4__ {int /*<<< orphan*/  name; int /*<<< orphan*/  userinfo; } ;

/* Variables and functions */
 int /*<<< orphan*/  Com_Error (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  ERR_DROP ; 
 char const* Info_ValueForKey (char const*,char*) ; 
 int /*<<< orphan*/  Q_strncpyz (int /*<<< orphan*/ ,char const*,int) ; 
 TYPE_3__* sv_maxclients ; 
 TYPE_2__ svs ; 

void SV_SetUserinfo( int index, const char *val ) {
	if ( index < 0 || index >= sv_maxclients->integer ) {
		Com_Error (ERR_DROP, "SV_SetUserinfo: bad index %i", index);
	}

	if ( !val ) {
		val = "";
	}

	Q_strncpyz( svs.clients[index].userinfo, val, sizeof( svs.clients[ index ].userinfo ) );
	Q_strncpyz( svs.clients[index].name, Info_ValueForKey( val, "name" ), sizeof(svs.clients[index].name) );
}