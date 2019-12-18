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
 int FNBUFF ; 
 scalar_t__ isspace (char const) ; 
 int sscanf (char const*,char*,void**,char*,int*) ; 

__attribute__((used)) static inline int
newfunction(const char *str)
{
	char fname[FNBUFF];
	void *ptr;
	int nbytes;

	if (isspace(str[0]))
		return (0);
	if (sscanf(str, "%p <%[^>:]>:%n", &ptr, fname, &nbytes) != 2)
		return (0);
	return (nbytes);
}