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
struct fst_session {int dummy; } ;
struct fst_group {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  MSG_ERROR ; 
 int /*<<< orphan*/  MSG_WARNING ; 
 int /*<<< orphan*/  fst_printf (int /*<<< orphan*/ ,char*,char const*) ; 
 struct fst_session* fst_session_create (struct fst_group*) ; 
 int /*<<< orphan*/  fst_session_get_id (struct fst_session*) ; 
 struct fst_group* get_fst_group_by_id (char const*) ; 
 int os_snprintf (char*,size_t,char*,...) ; 

__attribute__((used)) static int session_add(const char *group_id, char *buf, size_t buflen)
{
	struct fst_group *g;
	struct fst_session *s;

	g = get_fst_group_by_id(group_id);
	if (!g) {
		fst_printf(MSG_WARNING, "CTRL: Cannot find group '%s'",
			   group_id);
		return os_snprintf(buf, buflen, "FAIL\n");
	}

	s = fst_session_create(g);
	if (!s) {
		fst_printf(MSG_ERROR,
			   "CTRL: Cannot create session for group '%s'",
			   group_id);
		return os_snprintf(buf, buflen, "FAIL\n");
	}

	return os_snprintf(buf, buflen, "%u\n", fst_session_get_id(s));
}