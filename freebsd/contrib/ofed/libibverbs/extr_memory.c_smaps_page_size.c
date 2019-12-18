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
typedef  int /*<<< orphan*/  buf ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/ * fgets (char*,int,int /*<<< orphan*/ *) ; 
 unsigned long page_size ; 
 int sscanf (char*,char*,unsigned long*) ; 
 int /*<<< orphan*/  strstr (char*,char*) ; 

__attribute__((used)) static unsigned long smaps_page_size(FILE *file)
{
	int n;
	unsigned long size = page_size;
	char buf[1024];

	while (fgets(buf, sizeof(buf), file) != NULL) {
		if (!strstr(buf, "KernelPageSize:"))
			continue;

		n = sscanf(buf, "%*s %lu", &size);
		if (n < 1)
			continue;

		/* page size is printed in Kb */
		size = size * 1024;

		break;
	}

	return size;
}