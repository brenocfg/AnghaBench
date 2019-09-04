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
 int /*<<< orphan*/  fflush (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*,char*) ; 
 char* remote_ref ; 
 int /*<<< orphan*/  stdout ; 

__attribute__((used)) static int cmd_list(const char *line)
{
	printf("? %s\n\n", remote_ref);
	fflush(stdout);
	return 0;
}