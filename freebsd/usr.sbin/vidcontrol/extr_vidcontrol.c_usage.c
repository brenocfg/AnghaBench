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
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*,char*,char*,char*,char*,char*) ; 
 int /*<<< orphan*/  stderr ; 
 scalar_t__ vt4_mode ; 

__attribute__((used)) static void
usage(void)
{
	if (vt4_mode)
		fprintf(stderr, "%s\n%s\n%s\n%s\n%s\n%s\n",
"usage: vidcontrol [-CHPpx] [-b color] [-c appearance] [-f [[size] file]]",
"                  [-g geometry] [-h size] [-i active | adapter | mode]",
"                  [-M char] [-m on | off]",
"                  [-r foreground background] [-S on | off] [-s number]",
"                  [-T xterm | cons25] [-t N | off] [mode]",
"                  [foreground [background]] [show]");
	else
		fprintf(stderr, "%s\n%s\n%s\n%s\n%s\n%s\n",
"usage: vidcontrol [-CdHLPpx] [-b color] [-c appearance] [-E emulator]",
"                  [-f [[size] file]] [-g geometry] [-h size]",
"                  [-i active | adapter | mode] [-l screen_map] [-M char]",
"                  [-m on | off] [-r foreground background] [-S on | off]",
"                  [-s number] [-T xterm | cons25] [-t N | off] [mode]",
"                  [foreground [background]] [show]");
	exit(1);
}