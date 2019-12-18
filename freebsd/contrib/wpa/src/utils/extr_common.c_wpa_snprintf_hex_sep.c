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
typedef  int /*<<< orphan*/  u8 ;

/* Variables and functions */
 int os_snprintf (char*,int,char*,int /*<<< orphan*/  const,char) ; 
 scalar_t__ os_snprintf_error (int,int) ; 

int wpa_snprintf_hex_sep(char *buf, size_t buf_size, const u8 *data, size_t len,
			 char sep)
{
	size_t i;
	char *pos = buf, *end = buf + buf_size;
	int ret;

	if (buf_size == 0)
		return 0;

	for (i = 0; i < len; i++) {
		ret = os_snprintf(pos, end - pos, "%02x%c",
				  data[i], sep);
		if (os_snprintf_error(end - pos, ret)) {
			end[-1] = '\0';
			return pos - buf;
		}
		pos += ret;
	}
	pos[-1] = '\0';
	return pos - buf;
}