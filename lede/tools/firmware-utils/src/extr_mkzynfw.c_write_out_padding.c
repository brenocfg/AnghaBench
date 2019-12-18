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
struct csum_state {int dummy; } ;
typedef  int /*<<< orphan*/  buf ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,size_t) ; 
 scalar_t__ write_out_data (int /*<<< orphan*/ *,int /*<<< orphan*/ *,size_t,struct csum_state*) ; 

int
write_out_padding(FILE *outfile, size_t len, uint8_t padc,
		 struct csum_state *css)
{
	uint8_t buf[512];
	size_t buflen = sizeof(buf);

	memset(buf, padc, buflen);
	while (len > 0) {
		if (len < buflen)
			buflen = len;

		if (write_out_data(outfile, buf, buflen, css))
			return -1;

		len -= buflen;
	}

	return 0;
}