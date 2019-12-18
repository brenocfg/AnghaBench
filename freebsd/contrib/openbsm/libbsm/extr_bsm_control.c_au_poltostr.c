#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int ssize_t ;
struct TYPE_2__ {char* ap_str; int ap_policy; } ;

/* Variables and functions */
 TYPE_1__* au_polstr ; 
 size_t strlcat (char*,char*,size_t) ; 
 int strlen (char*) ; 

ssize_t
au_poltostr(int policy, size_t maxsize, char *buf)
{
	int first = 1;
	int i = 0;

	if (maxsize < 1)
		return (-1);
	buf[0] = '\0';

	do {
		if (policy & au_polstr[i].ap_policy) {
			if (!first && strlcat(buf, ",", maxsize) >= maxsize)
				return (-1);
			if (strlcat(buf, au_polstr[i].ap_str, maxsize) >=
			    maxsize)
				return (-1);
			first = 0;
		}
	} while (NULL != au_polstr[++i].ap_str);

	return (strlen(buf));
}