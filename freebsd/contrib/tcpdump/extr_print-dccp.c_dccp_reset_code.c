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

/* Variables and functions */
 size_t __DCCP_RESET_CODE_LAST ; 
 char const** dccp_reset_codes ; 

__attribute__((used)) static const char *dccp_reset_code(uint8_t code)
{
	if (code >= __DCCP_RESET_CODE_LAST)
		return "invalid";
	return dccp_reset_codes[code];
}