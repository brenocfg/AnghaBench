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
 int /*<<< orphan*/  printf (char const*,char const*) ; 

__attribute__((used)) static void show_file(const char * fmt, const char * name, int in_porcelain,
		      int * first, const char *header_msg)
{
	if (in_porcelain && *first && header_msg) {
		printf("%s\n", header_msg);
		*first = 0;
	}
	printf(fmt, name);
}