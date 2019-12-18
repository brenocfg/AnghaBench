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

void
usage()
{

	printf("usage: setkey [-v] -c\n");
	printf("       setkey [-v] -f filename\n");
	printf("       setkey [-Pagltv] -D\n");
	printf("       setkey [-Pv] -F\n");
	printf("       setkey [-h] -x\n");
	exit(1);
}