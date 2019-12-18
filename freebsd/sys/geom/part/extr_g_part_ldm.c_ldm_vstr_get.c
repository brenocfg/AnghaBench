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
typedef  size_t uint8_t ;
typedef  size_t u_char ;

/* Variables and functions */
 int /*<<< orphan*/  memcpy (size_t*,size_t const*,size_t) ; 

__attribute__((used)) static int
ldm_vstr_get(const u_char *buf, int offset, u_char *result,
    size_t maxlen, size_t range)
{
	uint8_t len;

	len = buf[offset++];
	if (len >= maxlen || len + offset >= range)
		return (-1);
	memcpy(result, buf + offset, len);
	result[len] = '\0';
	return (offset + len);
}