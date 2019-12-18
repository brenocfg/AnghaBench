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
 scalar_t__ isspace (char const) ; 
 int sscanf (char const*,char*,void**,int*) ; 

__attribute__((used)) static inline int
isasminline(const char *str)
{
	void *ptr;
	int nbytes;

	if (sscanf(str, " %p%n", &ptr, &nbytes) != 1)
		return (0);
	if (str[nbytes] != ':' || isspace(str[nbytes + 1]) == 0)
		return (0);
	return (1);
}