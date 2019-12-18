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
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*,char*,char*,char*) ; 
 int /*<<< orphan*/  stderr ; 

__attribute__((used)) static void
usage(void)
{
	(void)fprintf(stderr, "%s\n%s\n%s\n%s\n",
"usage: mount_nfs [-23bcdiLlNPsTU] [-a maxreadahead] [-D deadthresh]",
"                 [-g maxgroups] [-I readdirsize] [-o options] [-R retrycnt]",
"                 [-r readsize] [-t timeout] [-w writesize] [-x retrans]",
"                 rhost:path node");
	exit(1);
}