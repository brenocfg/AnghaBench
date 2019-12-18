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
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  stderr ; 

__attribute__((used)) static int
usage()
{
    fprintf(stderr, "usage: pppctl [-v] [-t n] [-p passwd] "
            "Port|LocalSock [command[;command]...]\n");
    fprintf(stderr, "              -v tells pppctl to output all"
            " conversation\n");
    fprintf(stderr, "              -t n specifies a timeout of n"
            " seconds when connecting (default 2)\n");
    fprintf(stderr, "              -p passwd specifies your password\n");
    exit(1);
}