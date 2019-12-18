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
typedef  int /*<<< orphan*/  pam_handle_t ;

/* Variables and functions */
 int PAM_NUM_ERRORS ; 
 char const** pam_err_text ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,int) ; 

const char *
pam_strerror(const pam_handle_t *pamh,
	int error_number)
{
	static char unknown[16];

	(void)pamh;
	if (error_number >= 0 && error_number < PAM_NUM_ERRORS) {
		return (pam_err_text[error_number]);
	} else {
		snprintf(unknown, sizeof unknown, "#%d", error_number);
		return (unknown);
	}
}