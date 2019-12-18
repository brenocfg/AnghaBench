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
 char* os_zalloc (int) ; 
 int /*<<< orphan*/  wpa_snprintf_hex (char*,int,int /*<<< orphan*/  const*,size_t) ; 

__attribute__((used)) static char * wpa_config_write_string_hex(const u8 *value, size_t len)
{
	char *buf;

	buf = os_zalloc(2 * len + 1);
	if (buf == NULL)
		return NULL;
	wpa_snprintf_hex(buf, 2 * len + 1, value, len);

	return buf;
}