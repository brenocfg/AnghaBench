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
struct fst_session {int /*<<< orphan*/  global_sessions_lentry; int /*<<< orphan*/  id; } ;

/* Variables and functions */
 int /*<<< orphan*/  MSG_INFO ; 
 int /*<<< orphan*/  dl_list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  foreach_fst_ctrl_call (int /*<<< orphan*/ ,struct fst_session*) ; 
 int /*<<< orphan*/  fst_printf (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  on_session_removed ; 
 int /*<<< orphan*/  os_free (struct fst_session*) ; 

void fst_session_delete(struct fst_session *s)
{
	fst_printf(MSG_INFO, "Session %u deleted", s->id);
	dl_list_del(&s->global_sessions_lentry);
	foreach_fst_ctrl_call(on_session_removed, s);
	os_free(s);
}