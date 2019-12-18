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
typedef  char int8_t ;

/* Variables and functions */

void
ata_btrim(int8_t *buf, int len)
{
	int8_t *ptr;

	for (ptr = buf; ptr < buf+len; ++ptr)
		if (!*ptr || *ptr == '_')
			*ptr = ' ';
	for (ptr = buf + len - 1; ptr >= buf && *ptr == ' '; --ptr)
		*ptr = 0;
}