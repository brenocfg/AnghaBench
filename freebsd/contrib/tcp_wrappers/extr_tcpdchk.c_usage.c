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
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 char* myname ; 
 int /*<<< orphan*/  stderr ; 

__attribute__((used)) static void usage(void)
{
    fprintf(stderr, "usage: %s [-a] [-d] [-i inet_conf] [-v]\n", myname);
    fprintf(stderr, "	-a: report rules with implicit \"ALLOW\" at end\n");
    fprintf(stderr, "	-d: use allow/deny files in current directory\n");
    fprintf(stderr, "	-i: location of inetd.conf file\n");
    fprintf(stderr, "	-v: list all rules\n");
    exit(1);
}