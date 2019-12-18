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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int /*<<< orphan*/  buff ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,size_t) ; 
 scalar_t__ write_out_data (int /*<<< orphan*/ *,int /*<<< orphan*/ *,size_t,int /*<<< orphan*/ *) ; 

int
write_out_padding(FILE *outfile, size_t len, uint8_t padc, uint32_t *crc)
{
	uint8_t buff[512];
	size_t  buflen = sizeof(buff);

	memset(buff, padc, buflen);

	while (len > 0) {
		if (len < buflen)
			buflen = len;

		if (write_out_data(outfile, buff, buflen, crc))
			return -1;

		len -= buflen;
	}

	return 0;
}