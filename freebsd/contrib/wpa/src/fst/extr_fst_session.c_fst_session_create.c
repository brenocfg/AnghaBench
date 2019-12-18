#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u32 ;
struct TYPE_2__ {int /*<<< orphan*/  llt_ms; } ;
struct fst_session {int /*<<< orphan*/  global_sessions_lentry; scalar_t__ id; TYPE_1__ data; int /*<<< orphan*/  state; struct fst_group* group; } ;
struct fst_group {int dummy; } ;

/* Variables and functions */
 scalar_t__ FST_INVALID_SESSION_ID ; 
 int /*<<< orphan*/  FST_LLT_MS_DEFAULT ; 
 int /*<<< orphan*/  FST_SESSION_STATE_INITIAL ; 
 int /*<<< orphan*/  MSG_ERROR ; 
 int /*<<< orphan*/  MSG_INFO ; 
 int /*<<< orphan*/  dl_list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  foreach_fst_ctrl_call (int /*<<< orphan*/ ,struct fst_session*) ; 
 scalar_t__ fst_find_free_session_id () ; 
 int /*<<< orphan*/  fst_printf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  global_sessions_list ; 
 int /*<<< orphan*/  on_session_added ; 
 struct fst_session* os_zalloc (int) ; 

struct fst_session * fst_session_create(struct fst_group *g)
{
	struct fst_session *s;
	u32 id;

	id = fst_find_free_session_id();
	if (id == FST_INVALID_SESSION_ID) {
		fst_printf(MSG_ERROR, "Cannot assign new session ID");
		return NULL;
	}

	s = os_zalloc(sizeof(*s));
	if (!s) {
		fst_printf(MSG_ERROR, "Cannot allocate new session object");
		return NULL;
	}

	s->id = id;
	s->group = g;
	s->state = FST_SESSION_STATE_INITIAL;

	s->data.llt_ms = FST_LLT_MS_DEFAULT;

	fst_printf(MSG_INFO, "Session %u created", s->id);

	dl_list_add_tail(&global_sessions_list, &s->global_sessions_lentry);

	foreach_fst_ctrl_call(on_session_added, s);

	return s;
}