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
 int /*<<< orphan*/  heap_bottom ; 
 int /*<<< orphan*/  heap_top ; 
 int /*<<< orphan*/  mallocstats () ; 
 int /*<<< orphan*/  printf (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sbrk (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
command_heap(int argc, char *argv[])
{
    mallocstats();
    printf("heap base at %p, top at %p, upper limit at %p\n", heap_bottom,
      sbrk(0), heap_top);
    return(CMD_OK);
}