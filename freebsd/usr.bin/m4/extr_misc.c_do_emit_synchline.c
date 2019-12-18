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
struct TYPE_2__ {int /*<<< orphan*/  lineno; int /*<<< orphan*/  synch_lineno; int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  active ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 size_t ilevel ; 
 TYPE_1__* infile ; 

void
do_emit_synchline(void)
{
	fprintf(active, "#line %lu \"%s\"\n",
	    infile[ilevel].lineno, infile[ilevel].name);
	infile[ilevel].synch_lineno = infile[ilevel].lineno;
}