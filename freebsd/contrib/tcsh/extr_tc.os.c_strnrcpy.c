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
 int strlen (char*) ; 

__attribute__((used)) static char *
strnrcpy(char *ptr, char *str, size_t siz)
{
    int len = strlen(str);
    if (siz == 0)
	return ptr;

    while (len && siz--)
	*--ptr = str[--len];

    return (ptr);
}