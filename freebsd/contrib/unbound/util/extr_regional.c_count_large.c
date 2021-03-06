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
struct regional {char* large_list; } ;

/* Variables and functions */

__attribute__((used)) static size_t
count_large(struct regional* r)
{
	size_t c = 0;
	char* p = r->large_list;
	while(p) {
		c++;
		p = *(char**)p;
	}
	return c;
}