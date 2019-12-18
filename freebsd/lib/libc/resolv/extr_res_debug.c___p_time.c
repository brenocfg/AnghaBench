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
typedef  int u_int32_t ;

/* Variables and functions */
 scalar_t__ ns_format_ttl (int,char*,int) ; 
 char* p_time_nbuf ; 
 int /*<<< orphan*/  sprintf (char*,char*,int) ; 

const char *
p_time(u_int32_t value) {
	char *nbuf = p_time_nbuf;

	if (ns_format_ttl(value, nbuf, sizeof nbuf) < 0)
		sprintf(nbuf, "%u", value);
	return (nbuf);
}