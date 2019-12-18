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
 int /*<<< orphan*/  printf (char*) ; 

__attribute__((used)) static void
usage()
{
	printf("usage: ndp [-nt] hostname\n");
	printf("       ndp [-nt] -a | -c | -p | -r | -H | -P | -R\n");
	printf("       ndp [-nt] -A wait\n");
	printf("       ndp [-nt] -d hostname\n");
	printf("       ndp [-nt] -f filename\n");
	printf("       ndp [-nt] -i interface [flags...]\n");
#ifdef SIOCSDEFIFACE_IN6
	printf("       ndp [-nt] -I [interface|delete]\n");
#endif
	printf("       ndp [-nt] -s nodename etheraddr [temp] [proxy]\n");
	exit(1);
}