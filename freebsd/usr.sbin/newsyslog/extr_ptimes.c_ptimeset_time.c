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
typedef  int /*<<< orphan*/  time_t ;
struct ptime_data {scalar_t__ parseopts; int /*<<< orphan*/  tsecs; int /*<<< orphan*/  tm; } ;

/* Variables and functions */
 int /*<<< orphan*/ * localtime (int /*<<< orphan*/ *) ; 

int
ptimeset_time(struct ptime_data *ptime, time_t secs)
{

	if (ptime == NULL)
		return (-1);

	ptime->tsecs = secs;
	ptime->tm = *(localtime(&ptime->tsecs));
	ptime->parseopts = 0;
	/* ptime->tmspec = ? */
	return (0);
}