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
 char* host_end (char**,int) ; 
 char* strchr (char*,char) ; 
 long strtol (char*,char**,int) ; 

__attribute__((used)) static void get_host_and_port(char **host, const char **port)
{
	char *colon, *end;
	end = host_end(host, 1);
	colon = strchr(end, ':');
	if (colon) {
		long portnr = strtol(colon + 1, &end, 10);
		if (end != colon + 1 && *end == '\0' && 0 <= portnr && portnr < 65536) {
			*colon = 0;
			*port = colon + 1;
		} else if (!colon[1]) {
			*colon = 0;
		}
	}
}