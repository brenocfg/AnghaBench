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
 int /*<<< orphan*/  strlcpy (char*,char const*,size_t) ; 
 char tolower (unsigned char) ; 

void
istrncpy(char *dest, const char *src, size_t dsize)
{

	strlcpy(dest, src, dsize);
	for (; *dest; dest++)
		*dest = tolower((unsigned char)*dest);
}