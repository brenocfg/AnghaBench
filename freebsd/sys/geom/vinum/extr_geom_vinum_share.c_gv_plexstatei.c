#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */

/* Variables and functions */
 int GV_PLEX_DEGRADED ; 
 int GV_PLEX_DOWN ; 
 int GV_PLEX_GROWABLE ; 
 int GV_PLEX_INITIALIZING ; 
 int GV_PLEX_UP ; 
 int /*<<< orphan*/  strcmp (char*,char*) ; 

int
gv_plexstatei(char *buf)
{
	if (!strcmp(buf, "up"))
		return (GV_PLEX_UP);
	else if (!strcmp(buf, "initializing"))
		return (GV_PLEX_INITIALIZING);
	else if (!strcmp(buf, "degraded"))
		return (GV_PLEX_DEGRADED);
	else if (!strcmp(buf, "growable"))
		return (GV_PLEX_GROWABLE);
	else
		return (GV_PLEX_DOWN);
}