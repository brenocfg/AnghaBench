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
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u32 ;
struct fst_session {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  FST_CS_PVAL_RESPONSE_ACCEPT ; 
 int /*<<< orphan*/  FST_CS_PVAL_RESPONSE_REJECT ; 
 int /*<<< orphan*/  MSG_INFO ; 
 int /*<<< orphan*/  MSG_WARNING ; 
 int /*<<< orphan*/  WLAN_STATUS_PENDING_ADMITTING_FST_SESSION ; 
 int /*<<< orphan*/  WLAN_STATUS_SUCCESS ; 
 int /*<<< orphan*/  fst_printf (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,...) ; 
 struct fst_session* fst_session_get_by_id (int /*<<< orphan*/ ) ; 
 scalar_t__ fst_session_respond (struct fst_session*,int /*<<< orphan*/ ) ; 
 int os_snprintf (char*,size_t,char*) ; 
 int /*<<< orphan*/  os_strcasecmp (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strtoul (char const*,char**,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int session_respond(const char *session_id, char *buf, size_t buflen)
{
	struct fst_session *s;
	char *p;
	u32 id;
	u8 status_code;

	id = strtoul(session_id, &p, 0);

	s = fst_session_get_by_id(id);
	if (!s) {
		fst_printf(MSG_WARNING, "CTRL: Cannot find session %u", id);
		return os_snprintf(buf, buflen, "FAIL\n");
	}

	if (*p != ' ')
		return os_snprintf(buf, buflen, "FAIL\n");
	p++;

	if (!os_strcasecmp(p, FST_CS_PVAL_RESPONSE_ACCEPT)) {
		status_code = WLAN_STATUS_SUCCESS;
	} else if (!os_strcasecmp(p, FST_CS_PVAL_RESPONSE_REJECT)) {
		status_code = WLAN_STATUS_PENDING_ADMITTING_FST_SESSION;
	} else {
		fst_printf(MSG_WARNING,
			   "CTRL: session %u: unknown response status: %s",
			   id, p);
		return os_snprintf(buf, buflen, "FAIL\n");
	}

	if (fst_session_respond(s, status_code)) {
		fst_printf(MSG_WARNING, "CTRL: Cannot respond to session %u",
			   id);
		return os_snprintf(buf, buflen, "FAIL\n");
	}

	fst_printf(MSG_INFO, "CTRL: session %u responded", id);

	return os_snprintf(buf, buflen, "OK\n");
}