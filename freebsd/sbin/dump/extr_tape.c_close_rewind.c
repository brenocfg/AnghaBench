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
typedef  scalar_t__ time_t ;

/* Variables and functions */
 int /*<<< orphan*/  broadcast (char*) ; 
 int /*<<< orphan*/  dumpabort (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msg (char*,scalar_t__) ; 
 scalar_t__ nexttape ; 
 int /*<<< orphan*/  nogripe ; 
 scalar_t__ query (char*) ; 
 scalar_t__ tapeno ; 
 int /*<<< orphan*/  time (scalar_t__*) ; 
 int /*<<< orphan*/  trewind () ; 
 int /*<<< orphan*/  tstart_writing ; 

void
close_rewind()
{
	time_t tstart_changevol, tend_changevol;

	trewind();
	if (nexttape)
		return;
	(void)time((time_t *)&(tstart_changevol));
	if (!nogripe) {
		msg("Change Volumes: Mount volume #%d\n", tapeno+1);
		broadcast("CHANGE DUMP VOLUMES!\a\a\n");
	}
	while (!query("Is the new volume mounted and ready to go?"))
		if (query("Do you want to abort?")) {
			dumpabort(0);
			/*NOTREACHED*/
		}
	(void)time((time_t *)&(tend_changevol));
	if ((tstart_changevol != (time_t)-1) && (tend_changevol != (time_t)-1))
		tstart_writing += (tend_changevol - tstart_changevol);
}