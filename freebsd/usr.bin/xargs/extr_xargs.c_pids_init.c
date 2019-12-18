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
 int /*<<< orphan*/ * childpids ; 
 int /*<<< orphan*/  clearslot (int) ; 
 int /*<<< orphan*/  errx (int,char*) ; 
 int /*<<< orphan*/ * malloc (int) ; 
 int maxprocs ; 

__attribute__((used)) static void
pids_init(void)
{
	int i;

	if ((childpids = malloc(maxprocs * sizeof(*childpids))) == NULL)
		errx(1, "malloc failed");

	for (i = 0; i < maxprocs; i++)
		clearslot(i);
}