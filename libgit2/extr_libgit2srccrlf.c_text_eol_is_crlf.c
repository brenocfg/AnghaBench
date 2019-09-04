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
struct crlf_attrs {scalar_t__ auto_crlf; scalar_t__ core_eol; } ;

/* Variables and functions */
 scalar_t__ GIT_AUTO_CRLF_INPUT ; 
 scalar_t__ GIT_AUTO_CRLF_TRUE ; 
 scalar_t__ GIT_EOL_CRLF ; 
 scalar_t__ GIT_EOL_NATIVE ; 
 scalar_t__ GIT_EOL_UNSET ; 

__attribute__((used)) static int text_eol_is_crlf(struct crlf_attrs *ca)
{
	if (ca->auto_crlf == GIT_AUTO_CRLF_TRUE)
		return 1;
	else if (ca->auto_crlf == GIT_AUTO_CRLF_INPUT)
		return 0;

	if (ca->core_eol == GIT_EOL_CRLF)
		return 1;
	if (ca->core_eol == GIT_EOL_UNSET && GIT_EOL_NATIVE == GIT_EOL_CRLF)
		return 1;

	return 0;
}