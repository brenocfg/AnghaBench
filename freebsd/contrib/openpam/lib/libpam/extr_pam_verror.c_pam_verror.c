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
typedef  int /*<<< orphan*/  va_list ;
typedef  int /*<<< orphan*/  pam_handle_t ;

/* Variables and functions */
 int /*<<< orphan*/  FREE (char*) ; 
 int /*<<< orphan*/  PAM_ERROR_MSG ; 
 int pam_vprompt (int /*<<< orphan*/  const*,int /*<<< orphan*/ ,char**,char const*,int /*<<< orphan*/ ) ; 

int
pam_verror(const pam_handle_t *pamh,
	const char *fmt,
	va_list ap)
{
	char *rsp;
	int r;

	r = pam_vprompt(pamh, PAM_ERROR_MSG, &rsp, fmt, ap);
	FREE(rsp); /* ignore response */
	return (r);
}