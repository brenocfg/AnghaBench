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
typedef  char uint8_t ;
typedef  int uint32_t ;
typedef  int uint16_t ;
typedef  int /*<<< orphan*/  elink_status_t ;

/* Variables and functions */
 int /*<<< orphan*/  ELINK_STATUS_ERROR ; 
 int /*<<< orphan*/  ELINK_STATUS_OK ; 

__attribute__((used)) static elink_status_t elink_7101_format_ver(uint32_t spirom_ver, uint8_t *str, uint16_t *len)
{
	if (*len < 5)
		return ELINK_STATUS_ERROR;
	str[0] = (spirom_ver & 0xFF);
	str[1] = (spirom_ver & 0xFF00) >> 8;
	str[2] = (spirom_ver & 0xFF0000) >> 16;
	str[3] = (spirom_ver & 0xFF000000) >> 24;
	str[4] = '\0';
	*len -= 5;
	return ELINK_STATUS_OK;
}