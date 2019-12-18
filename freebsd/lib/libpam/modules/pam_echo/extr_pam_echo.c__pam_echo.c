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
typedef  int /*<<< orphan*/  msg ;

/* Variables and functions */
 int PAM_MAX_MSG_SIZE ; 
 int PAM_RHOST ; 
 int PAM_RUSER ; 
 int PAM_SERVICE ; 
 int PAM_SILENT ; 
 int PAM_SUCCESS ; 
 int PAM_TTY ; 
 int PAM_USER ; 
 int pam_get_item (int /*<<< orphan*/ *,int,void const**) ; 
 int pam_info (int /*<<< orphan*/ *,char*,char*) ; 

__attribute__((used)) static int
_pam_echo(pam_handle_t *pamh, int flags,
    int argc, const char *argv[])
{
	char msg[PAM_MAX_MSG_SIZE];
	const void *str;
	const char *p, *q;
	int err, i, item;
	size_t len;

	if (flags & PAM_SILENT)
		return (PAM_SUCCESS);
	for (i = 0, len = 0; i < argc && len < sizeof(msg) - 1; ++i) {
		if (i > 0)
			msg[len++] = ' ';
		for (p = argv[i]; *p != '\0' && len < sizeof(msg) - 1; ++p) {
			if (*p != '%' || p[1] == '\0') {
				msg[len++] = *p;
				continue;
			}
			switch (*++p) {
			case 'H':
				item = PAM_RHOST;
				break;
			case 'h':
				/* not implemented */
				item = -1;
				break;
			case 's':
				item = PAM_SERVICE;
				break;
			case 't':
				item = PAM_TTY;
				break;
			case 'U':
				item = PAM_RUSER;
				break;
			case 'u':
				item = PAM_USER;
				break;
			default:
				item = -1;
				msg[len++] = *p;
				break;
			}
			if (item == -1)
				continue;
			err = pam_get_item(pamh, item, &str);
			if (err != PAM_SUCCESS)
				return (err);
			if (str == NULL)
				str = "(null)";
			for (q = str; *q != '\0' && len < sizeof(msg) - 1; ++q)
				msg[len++] = *q;
		}
	}
	msg[len] = '\0';
	return (pam_info(pamh, "%s", msg));
}