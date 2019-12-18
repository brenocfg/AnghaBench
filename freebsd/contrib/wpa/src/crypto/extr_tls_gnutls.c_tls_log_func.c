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
 int /*<<< orphan*/  MSG_DEBUG ; 
 int /*<<< orphan*/  MSG_MSGDUMP ; 
 int /*<<< orphan*/  os_free (char*) ; 
 char* os_strdup (char const*) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*,int,char*) ; 

__attribute__((used)) static void tls_log_func(int level, const char *msg)
{
	char *s, *pos;
	if (level == 6 || level == 7) {
		/* These levels seem to be mostly I/O debug and msg dumps */
		return;
	}

	s = os_strdup(msg);
	if (s == NULL)
		return;

	pos = s;
	while (*pos != '\0') {
		if (*pos == '\n') {
			*pos = '\0';
			break;
		}
		pos++;
	}
	wpa_printf(level > 3 ? MSG_MSGDUMP : MSG_DEBUG,
		   "gnutls<%d> %s", level, s);
	os_free(s);
}