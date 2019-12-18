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
 scalar_t__ atol (char*) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 scalar_t__ restart_point ; 

void
restart(int argc, char **argv)
{

    if (argc != 2)
	printf("restart: offset not specified\n");
    else {
	restart_point = atol(argv[1]);
	printf("restarting at %ld. %s\n", (long)restart_point,
	       "execute get, put or append to initiate transfer");
    }
}