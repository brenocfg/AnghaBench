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
 int /*<<< orphan*/  die (char*,int) ; 
 char* strtok (int /*<<< orphan*/ *,char*) ; 

__attribute__((used)) static void get_s(int line_nr, char **s_in)
{
	*s_in = strtok(NULL, " ");
	if (!*s_in)
		die("line[%d]: expected: <s>", line_nr);
}