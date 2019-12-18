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
struct fst_group {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  MSG_WARNING ; 
 int /*<<< orphan*/  fst_group_delete_if_empty (struct fst_group*) ; 
 int /*<<< orphan*/  fst_printf (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fst_session_delete (struct fst_session*) ; 
 struct fst_session* fst_session_get_by_id (int /*<<< orphan*/ ) ; 
 struct fst_group* fst_session_get_group (struct fst_session*) ; 
 int /*<<< orphan*/  fst_session_reset (struct fst_session*) ; 
 int os_snprintf (char*,size_t,char*) ; 
 int /*<<< orphan*/  strtoul (char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int session_remove(const char *session_id, char *buf, size_t buflen)
{
	struct fst_session *s;
	struct fst_group *g;
	u32 id;

	id = strtoul(session_id, NULL, 0);

	s = fst_session_get_by_id(id);
	if (!s) {
		fst_printf(MSG_WARNING, "CTRL: Cannot find session %u", id);
		return os_snprintf(buf, buflen, "FAIL\n");
	}

	g = fst_session_get_group(s);
	fst_session_reset(s);
	fst_session_delete(s);
	fst_group_delete_if_empty(g);

	return os_snprintf(buf, buflen, "OK\n");
}