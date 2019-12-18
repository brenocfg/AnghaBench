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
typedef  int /*<<< orphan*/  u32 ;
struct fst_session {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  MSG_WARNING ; 
 int /*<<< orphan*/  fst_printf (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 struct fst_session* fst_session_get_by_id (int /*<<< orphan*/ ) ; 
 scalar_t__ fst_session_tear_down_setup (struct fst_session*) ; 
 int os_snprintf (char*,size_t,char*) ; 
 int /*<<< orphan*/  strtoul (char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int session_teardown(const char *session_id, char *buf, size_t buflen)
{
	struct fst_session *s;
	u32 id;

	id = strtoul(session_id, NULL, 0);

	s = fst_session_get_by_id(id);
	if (!s) {
		fst_printf(MSG_WARNING, "CTRL: Cannot find session %u", id);
		return os_snprintf(buf, buflen, "FAIL\n");
	}

	if (fst_session_tear_down_setup(s)) {
		fst_printf(MSG_WARNING, "CTRL: Cannot tear down session %u",
			   id);
		return os_snprintf(buf, buflen, "FAIL\n");
	}

	return os_snprintf(buf, buflen, "OK\n");
}