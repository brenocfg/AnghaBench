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
 scalar_t__ havehost ; 
 scalar_t__ numassoc ; 
 scalar_t__ numcmds ; 
 scalar_t__ numhosts ; 
 int /*<<< orphan*/ * server_entry ; 
 scalar_t__ showhostnames ; 

void clear_globals(void)
{
	extern int ntp_optind;
	showhostnames = 0;	/* don'tshow host names by default */
	ntp_optind = 0;
	server_entry = NULL;	/* server entry for ntp */
	havehost = 0;		/* set to 1 when host open */
	numassoc = 0;		/* number of cached associations */
	numcmds = 0;
	numhosts = 0;
}