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
 size_t SPRINTF (char*) ; 
 int /*<<< orphan*/  strcpy (char*,char*) ; 

__attribute__((used)) static int
fmt1(int t, char s, char **buf, size_t *buflen) {
	char tmp[50];
	size_t len;

	len = SPRINTF((tmp, "%d%c", t, s));
	if (len + 1 > *buflen)
		return (-1);
	strcpy(*buf, tmp);
	*buf += len;
	*buflen -= len;
	return (0);
}