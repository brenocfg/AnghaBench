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
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 scalar_t__ iicbb_readbyte (int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static int
iicbb_read(device_t dev, char * buf, int len, int *read, int last, int delay)
{
	int bytes;

	bytes = 0;
	while (len) {
		/* XXX should insert delay here */
		*buf++ = (char)iicbb_readbyte(dev, (len == 1) ? last : 0, delay);

		bytes ++;
		len --;
	}

	*read = bytes;
	return (0);
}