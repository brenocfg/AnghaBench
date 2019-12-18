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
struct skip_range {void* end; void* start; } ;

/* Variables and functions */
 int /*<<< orphan*/  atoi (char*) ; 
 char* strsep (char**,char*) ; 
 void* strtoul (char*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static struct skip_range
skip_get_range(char *skip_addr)
{
	struct skip_range addr_range;
	char *token;

	addr_range.start = 0;
	addr_range.end = 0;

	token = strsep(&skip_addr, "..");
	if (token) {
		addr_range.start = strtoul(token, 0, 16);
		token = strsep(&skip_addr, "..");
		if ((token != NULL) && !atoi(token)) {
			token = strsep(&skip_addr, "..");
			if (token)
				addr_range.end = strtoul(token, 0, 16);
		}
	}

	return (addr_range);
}