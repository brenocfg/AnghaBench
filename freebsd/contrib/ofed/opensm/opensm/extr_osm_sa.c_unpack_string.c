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
typedef  char uint8_t ;

/* Variables and functions */

__attribute__((used)) static int unpack_string(char *p, uint8_t * buf, unsigned len)
{
	char *q = p;
	char delim = ' ';

	if (*q == '\'' || *q == '\"')
		delim = *q++;
	while (--len && *q && *q != delim)
		*buf++ = *q++;
	*buf = '\0';
	if (*q == delim && delim != ' ')
		q++;
	return (int)(q - p);
}