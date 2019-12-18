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
typedef  int u_int8_t ;

/* Variables and functions */
 int PF_TH_ALL ; 
 char* strchr (char*,char) ; 
 char* tcpflags ; 

int
parse_flags(char *s)
{
	char		*p, *q;
	u_int8_t	 f = 0;

	for (p = s; *p; p++) {
		if ((q = strchr(tcpflags, *p)) == NULL)
			return -1;
		else
			f |= 1 << (q - tcpflags);
	}
	return (f ? f : PF_TH_ALL);
}