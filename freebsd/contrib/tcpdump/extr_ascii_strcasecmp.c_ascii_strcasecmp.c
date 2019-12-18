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
 unsigned char* charmap ; 

int
ascii_strcasecmp(const char *s1, const char *s2)
{
	register const unsigned char *cm = charmap,
			*us1 = (const unsigned char *)s1,
			*us2 = (const unsigned char *)s2;

	while (cm[*us1] == cm[*us2++])
		if (*us1++ == '\0')
			return(0);
	return(cm[*us1] - cm[*--us2]);
}