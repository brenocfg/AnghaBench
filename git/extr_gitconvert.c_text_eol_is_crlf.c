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

/* Variables and functions */
 scalar_t__ AUTO_CRLF_INPUT ; 
 scalar_t__ AUTO_CRLF_TRUE ; 
 scalar_t__ EOL_CRLF ; 
 scalar_t__ EOL_NATIVE ; 
 scalar_t__ EOL_UNSET ; 
 scalar_t__ auto_crlf ; 
 scalar_t__ core_eol ; 

__attribute__((used)) static int text_eol_is_crlf(void)
{
	if (auto_crlf == AUTO_CRLF_TRUE)
		return 1;
	else if (auto_crlf == AUTO_CRLF_INPUT)
		return 0;
	if (core_eol == EOL_CRLF)
		return 1;
	if (core_eol == EOL_UNSET && EOL_NATIVE == EOL_CRLF)
		return 1;
	return 0;
}