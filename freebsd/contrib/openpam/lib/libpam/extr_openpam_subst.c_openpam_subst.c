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
 int /*<<< orphan*/  ENTERS (char const*) ; 
 int /*<<< orphan*/  PAM_HOST ; 
 int /*<<< orphan*/  PAM_RHOST ; 
 int /*<<< orphan*/  PAM_RUSER ; 
 int /*<<< orphan*/  PAM_SERVICE ; 
 int PAM_SUCCESS ; 
 int PAM_TRY_AGAIN ; 
 int /*<<< orphan*/  PAM_TTY ; 
 int /*<<< orphan*/  PAM_USER ; 
 int /*<<< orphan*/  RETURNC (int) ; 
 int /*<<< orphan*/  subst_char (char const) ; 
 int /*<<< orphan*/  subst_item (int /*<<< orphan*/ ) ; 

int
openpam_subst(const pam_handle_t *pamh,
    char *buf, size_t *bufsize, const char *template)
{
	size_t len;
	int ret;

	ENTERS(template);
	if (template == NULL)
		template = "(null)";

	len = 1; /* initialize to 1 for terminating NUL */
	ret = PAM_SUCCESS;
	while (*template && ret == PAM_SUCCESS) {
		if (template[0] == '%') {
			++template;
			switch (*template) {
			case 's':
				subst_item(PAM_SERVICE);
				break;
			case 't':
				subst_item(PAM_TTY);
				break;
			case 'h':
				subst_item(PAM_HOST);
				break;
			case 'u':
				subst_item(PAM_USER);
				break;
			case 'H':
				subst_item(PAM_RHOST);
				break;
			case 'U':
				subst_item(PAM_RUSER);
				break;
			case '\0':
				subst_char('%');
				break;
			default:
				subst_char('%');
				subst_char(*template);
			}
			++template;
		} else {
			subst_char(*template++);
		}
	}
	if (buf)
		*buf = '\0';
	if (ret == PAM_SUCCESS) {
		if (len > *bufsize)
			ret = PAM_TRY_AGAIN;
		*bufsize = len;
	}
	RETURNC(ret);
}