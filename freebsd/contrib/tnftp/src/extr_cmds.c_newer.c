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
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*,char*) ; 
 scalar_t__ getit (int,char**,int,char*) ; 
 int /*<<< orphan*/  ttyout ; 

void
newer(int argc, char *argv[])
{

	if (getit(argc, argv, -1, "w"))
		fprintf(ttyout,
		    "Local file \"%s\" is newer than remote file \"%s\".\n",
		    argv[2], argv[1]);
}