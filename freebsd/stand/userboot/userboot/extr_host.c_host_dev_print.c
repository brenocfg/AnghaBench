#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  line ;
struct TYPE_2__ {char* dv_name; } ;

/* Variables and functions */
 TYPE_1__ host_dev ; 
 int pager_output (char*) ; 
 int /*<<< orphan*/  printf (char*,char*) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
host_dev_print(int verbose)
{
	char line[80];

	printf("%s devices:", host_dev.dv_name);
	if (pager_output("\n") != 0)
		return (1);

	snprintf(line, sizeof(line), "    host%d:   Host filesystem\n", 0);
	return (pager_output(line));
}