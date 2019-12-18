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
 scalar_t__ hexstr2bin (char const*,int /*<<< orphan*/ *,size_t) ; 
 int /*<<< orphan*/  os_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * os_malloc (size_t) ; 
 int os_strlen (char const*) ; 

__attribute__((used)) static u8 * eap_fast_parse_hex(const char *value, size_t *len)
{
	int hlen;
	u8 *buf;

	if (value == NULL)
		return NULL;
	hlen = os_strlen(value);
	if (hlen & 1)
		return NULL;
	*len = hlen / 2;
	buf = os_malloc(*len);
	if (buf == NULL)
		return NULL;
	if (hexstr2bin(value, buf, *len)) {
		os_free(buf);
		return NULL;
	}
	return buf;
}