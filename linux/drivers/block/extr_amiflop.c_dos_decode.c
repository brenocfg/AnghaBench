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
typedef  unsigned long ulong ;

/* Variables and functions */
 int /*<<< orphan*/  dos_decode_byte (int /*<<< orphan*/ ) ; 

__attribute__((used)) static unsigned long dos_decode(unsigned char *data, unsigned short *raw, int len)
{
	int i;

	for (i = 0; i < len; i++)
		*data++=dos_decode_byte(*raw++);
	return ((ulong)raw);
}