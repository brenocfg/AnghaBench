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
 int /*<<< orphan*/  err (int,char*,char const*) ; 
 int /*<<< orphan*/  fclose (scalar_t__) ; 
 scalar_t__ fopen (char const*,char*) ; 
 scalar_t__ stderr ; 
 scalar_t__ traceout ; 

void
trace_file(const char *name)
{

	if (traceout && traceout != stderr)
		fclose(traceout);
	traceout = fopen(name, "w");
	if (!traceout)
		err(1, "can't open %s", name);
}