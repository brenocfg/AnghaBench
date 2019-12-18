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
typedef  int /*<<< orphan*/  WOLFSSL_X509 ;

/* Variables and functions */
 int GEN_DNS ; 
 int GEN_EMAIL ; 
 int GEN_URI ; 
 int /*<<< orphan*/  MSG_INFO ; 
 char* os_strchr (char const*,char) ; 
 size_t os_strlen (char const*) ; 
 scalar_t__ os_strncmp (char const*,char*,int) ; 
 scalar_t__ tls_match_alt_subject_component (int /*<<< orphan*/ *,int,char const*,size_t) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*,char const*) ; 

__attribute__((used)) static int tls_match_alt_subject(WOLFSSL_X509 *cert, const char *match)
{
	int type;
	const char *pos, *end;
	size_t len;

	pos = match;
	do {
		if (os_strncmp(pos, "EMAIL:", 6) == 0) {
			type = GEN_EMAIL;
			pos += 6;
		} else if (os_strncmp(pos, "DNS:", 4) == 0) {
			type = GEN_DNS;
			pos += 4;
		} else if (os_strncmp(pos, "URI:", 4) == 0) {
			type = GEN_URI;
			pos += 4;
		} else {
			wpa_printf(MSG_INFO,
				   "TLS: Invalid altSubjectName match '%s'",
				   pos);
			return 0;
		}
		end = os_strchr(pos, ';');
		while (end) {
			if (os_strncmp(end + 1, "EMAIL:", 6) == 0 ||
			    os_strncmp(end + 1, "DNS:", 4) == 0 ||
			    os_strncmp(end + 1, "URI:", 4) == 0)
				break;
			end = os_strchr(end + 1, ';');
		}
		if (end)
			len = end - pos;
		else
			len = os_strlen(pos);
		if (tls_match_alt_subject_component(cert, type, pos, len) > 0)
			return 1;
		pos = end + 1;
	} while (end);

	return 0;
}