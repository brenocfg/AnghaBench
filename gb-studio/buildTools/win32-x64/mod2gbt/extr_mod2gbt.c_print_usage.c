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
 int DEFAULT_ROM_BANK ; 
 int /*<<< orphan*/  printf (char*,...) ; 

void print_usage(void)
{
    printf("Usage: mod2gtb modfile.mod label_name [-c/-a] N\n\n");
    printf("       -c: Write GBDK output.c file.\n");
    printf("       -a: Write RGBDS output.asm file.\n");
    printf("       N: Set output to ROM bank N. If not defined, it will be %d.",DEFAULT_ROM_BANK);
    printf("\n\n");
}