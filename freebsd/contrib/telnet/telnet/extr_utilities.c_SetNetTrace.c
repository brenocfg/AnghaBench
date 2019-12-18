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
 scalar_t__ NetTrace ; 
 scalar_t__ NetTraceFile ; 
 int /*<<< orphan*/  fclose (scalar_t__) ; 
 scalar_t__ fopen (char*,char*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  stderr ; 
 scalar_t__ stdout ; 
 scalar_t__ strcmp (char*,char*) ; 
 int /*<<< orphan*/  strcpy (char*,char*) ; 

void
SetNetTrace(char *file)
{
    if (NetTrace && NetTrace != stdout)
	fclose(NetTrace);
    if (file  && (strcmp(file, "-") != 0)) {
	NetTrace = fopen(file, "w");
	if (NetTrace) {
	    strcpy((char *)NetTraceFile, file);
	    return;
	}
	fprintf(stderr, "Cannot open %s.\n", file);
    }
    NetTrace = stdout;
    strcpy((char *)NetTraceFile, "(standard output)");
}