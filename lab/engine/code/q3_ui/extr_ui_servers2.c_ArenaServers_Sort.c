#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  servernode_t ;
struct TYPE_2__ {int /*<<< orphan*/ * numservers; int /*<<< orphan*/  serverlist; } ;

/* Variables and functions */
 int /*<<< orphan*/  ArenaServers_Compare ; 
 TYPE_1__ g_arenaservers ; 
 int g_sortkey ; 
 int /*<<< orphan*/  qsort (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

void ArenaServers_Sort( int type ) {
	if( g_sortkey == type ) {
		return;
	}

	g_sortkey = type;
	qsort( g_arenaservers.serverlist, *g_arenaservers.numservers, sizeof( servernode_t ), ArenaServers_Compare);
}