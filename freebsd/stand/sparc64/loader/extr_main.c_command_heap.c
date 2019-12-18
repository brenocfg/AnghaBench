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
 int CMD_OK ; 
 scalar_t__ HEAPSZ ; 
 scalar_t__ heapva ; 
 int /*<<< orphan*/  mallocstats () ; 
 int /*<<< orphan*/  printf (char*,scalar_t__,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  sbrk (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
command_heap(int argc, char *argv[])
{

	mallocstats();
	printf("heap base at %p, top at %p, upper limit at %p\n", heapva,
	    sbrk(0), heapva + HEAPSZ);
	return(CMD_OK);
}