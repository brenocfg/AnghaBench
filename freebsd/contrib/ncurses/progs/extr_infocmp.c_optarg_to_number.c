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
 int /*<<< orphan*/  EXIT_FAILURE ; 
 int /*<<< orphan*/  ExitProgram (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*) ; 
 char* optarg ; 
 int /*<<< orphan*/  stderr ; 
 long strtol (char*,char**,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
optarg_to_number(void)
{
    char *temp = 0;
    long value = strtol(optarg, &temp, 0);

    if (temp == 0 || temp == optarg || *temp != 0) {
	fprintf(stderr, "Expected a number, not \"%s\"\n", optarg);
	ExitProgram(EXIT_FAILURE);
    }
    return (int) value;
}