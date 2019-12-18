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
 scalar_t__ is_hex (int /*<<< orphan*/  const*,size_t) ; 
 char* wpa_config_write_string_ascii (int /*<<< orphan*/  const*,size_t) ; 
 char* wpa_config_write_string_hex (int /*<<< orphan*/  const*,size_t) ; 

__attribute__((used)) static char * wpa_config_write_string(const u8 *value, size_t len)
{
	if (value == NULL)
		return NULL;

	if (is_hex(value, len))
		return wpa_config_write_string_hex(value, len);
	else
		return wpa_config_write_string_ascii(value, len);
}