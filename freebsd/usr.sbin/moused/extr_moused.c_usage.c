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
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*,char*,char*,char*,char*) ; 
 int /*<<< orphan*/  stderr ; 

__attribute__((used)) static void
usage(void)
{
    fprintf(stderr, "%s\n%s\n%s\n%s\n%s\n",
	"usage: moused [-DRcdfs] [-I file] [-F rate] [-r resolution] [-S baudrate]",
	"              [-VH [-U threshold]] [-a X[,Y]] [-C threshold] [-m N=M] [-w N]",
	"              [-z N] [-t <mousetype>] [-l level] [-3 [-E timeout]]",
	"              [-T distance[,time[,after]]] -p <port>",
	"       moused [-d] -i <port|if|type|model|all> -p <port>");
    exit(1);
}