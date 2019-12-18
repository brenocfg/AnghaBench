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
 int /*<<< orphan*/  PKFILE ; 
 int /*<<< orphan*/  PKMAP ; 
 int /*<<< orphan*/  YPOP_STORE ; 
 int localupdate (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,char*) ; 
 int mapupdate (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  sprintf (char*,char*,char*,char*) ; 
 int /*<<< orphan*/  strlen (char*) ; 

int
setpublicmap(char *name, char *public, char *secret)
{
	char pkent[1024];

	(void)sprintf(pkent, "%s:%s", public, secret);
#ifdef YP
	return (mapupdate(name, PKMAP, YPOP_STORE,
		strlen(name), name, strlen(pkent), pkent));
#else
	return (localupdate(name, PKFILE, YPOP_STORE,
		strlen(name), name, strlen(pkent), pkent));
#endif
	}