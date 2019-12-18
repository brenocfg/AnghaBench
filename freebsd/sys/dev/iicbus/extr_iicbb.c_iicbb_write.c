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
typedef  int /*<<< orphan*/  u_char ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int iicbb_ack (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  iicbb_sendbyte (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int
iicbb_write(device_t dev, const char *buf, int len, int *sent, int timeout)
{
	int bytes, error = 0;

	bytes = 0;
	while (len) {
		/* send byte */
		iicbb_sendbyte(dev,(u_char)*buf++, timeout);

		/* check for ack */
		error = iicbb_ack(dev, timeout);
		if (error != 0)
			break;
		bytes++;
		len--;
	}

	*sent = bytes;
	return (error);
}