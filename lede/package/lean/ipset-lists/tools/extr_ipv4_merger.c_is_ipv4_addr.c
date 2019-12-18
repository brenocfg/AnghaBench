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
 int sscanf (char const*,char*,int*,int*,int*,int*) ; 

__attribute__((used)) static inline bool is_ipv4_addr(const char *s)
{
	int u[4];
	if (sscanf(s, "%d.%d.%d.%d", &u[0], &u[1], &u[2], &u[3]) == 4)
		return true;
	else
		return false;
}